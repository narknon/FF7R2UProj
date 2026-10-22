#include "RebirthSafeLoad.h"

#include "CoreGlobals.h"
#include "HAL/IConsoleManager.h"
#include "Misc/CommandLine.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/Parse.h"
#include "Misc/ScopeLock.h"
#include "Misc/SecureHash.h"
#include "Modules/ModuleManager.h"
#include "Serialization/Archive.h"
#include "Serialization/StructuredArchive.h"
#include "UObject/Class.h"
#include "UObject/LinkerLoad.h"
#include "UObject/Package.h"
#include "UObject/UnrealType.h"
#include "UObject/UObjectThreadContext.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#include <Windows.h>
#include "Windows/HideWindowsPlatformTypes.h"
#endif

DEFINE_LOG_CATEGORY_STATIC(LogRebirthSafeLoad, Log, All);

namespace RebirthSafeLoadPrivate
{
	// FLinkerLoad::Loader is private. Naming it in an explicit instantiation is allowed (access isn't checked there),
	// which gives a member pointer to it.
	template <typename Tag, typename Tag::Type Member>
	struct TPrivateMember
	{
		friend typename Tag::Type GetPrivateMember(Tag) { return Member; }
	};

	struct FLinkerLoaderTag
	{
		using Type = FArchive* FLinkerLoad::*;
		friend Type GetPrivateMember(FLinkerLoaderTag);
	};

	template struct TPrivateMember<FLinkerLoaderTag, &FLinkerLoad::Loader>;

	FArchive*& LoaderOf(FLinkerLoad& Linker)
	{
		return Linker.*GetPrivateMember(FLinkerLoaderTag());
	}

	// SerializeUnversionedProperties in RebirthEngineV5's UE4Editor-CoreUObject.dll (not exported). The whole function
	// is checked before it is patched, so any other build of the DLL leaves the guard off.
	constexpr uint32 ExpectedTimeDateStamp = 0x6A242105;
	constexpr uint32 ExpectedSizeOfImage = 0x76D000;
	constexpr uint32 TargetRva = 0x2845A0;
	constexpr uint32 TargetSize = 3496;
	const TCHAR* const ExpectedSha1 = TEXT("43860A718848D02A3B7BD6A93133686714C1650E");
	// push rbp; push rbx; push rsi; push rdi; push r12-r15; sub rsp, 488h: position-independent, moved to the trampoline.
	constexpr int32 PrologueSize = 20;
	const uint8 ExpectedPrologue[PrologueSize] = { 0x40, 0x55, 0x53, 0x56, 0x57, 0x41, 0x54, 0x41, 0x55, 0x41, 0x56, 0x41, 0x57, 0x48, 0x81, 0xEC, 0x88, 0x04, 0x00, 0x00 };
	constexpr int32 JumpSize = 14;

	using FSerializeUnversionedFn = void (*)(const UStruct*, FStructuredArchive::FSlot, uint8*, UStruct*, uint8*);

	FSerializeUnversionedFn GOriginal = nullptr;
	uint8* GTarget = nullptr;
	uint8 GSavedBytes[JumpSize] = {};
	bool GActive = false;
	FString GInactiveReason = TEXT("not started");

	FCriticalSection GLock;
	TMap<FName, FString> GDamaged;
	TSet<FString> GReported;

	// In a cook (-run=Cook) the guard only stands in for packages the cook leaves out, so it never writes an object it
	// could not read in full: Directories To Never Cook, and what other modules leave out (AddPackagesLeftOutOfCook).
	bool GCookMode = false;
	bool GNeverCookRootsRead = false;
	TArray<FString> GNeverCookRoots;   // "/Game/Motion/"
	TSet<FName> GLeftOutOfCook;

	bool IsCookCommandlet()
	{
		FString Commandlet;
		return FParse::Value(FCommandLine::Get(), TEXT("-run="), Commandlet) && Commandlet.StartsWith(TEXT("Cook"), ESearchCase::IgnoreCase);
	}

	/** Project Settings > Packaging > Directories To Never Cook, as package path prefixes (read once, under GLock). */
	void ReadNeverCookRootsLocked()
	{
		if (GNeverCookRootsRead || !GConfig)
		{
			return;
		}
		GNeverCookRootsRead = true;
		TArray<FString> Entries;
		GConfig->GetArray(TEXT("/Script/UnrealEd.ProjectPackagingSettings"), TEXT("DirectoriesToNeverCook"), Entries, GGameIni);
		for (const FString& Entry : Entries)
		{
			FString Root;
			if (!FParse::Value(*Entry, TEXT("Path="), Root))
			{
				continue;
			}
			Root = Root.TrimStartAndEnd().Replace(TEXT("\\"), TEXT("/"));
			if (Root.IsEmpty())
			{
				continue;
			}
			if (!Root.StartsWith(TEXT("/")))
			{
				Root = TEXT("/Game/") + Root;
			}
			while (Root.EndsWith(TEXT("/")))
			{
				Root.LeftChopInline(1);
			}
			GNeverCookRoots.AddUnique(Root + TEXT("/"));
		}
	}

	/** The cook leaves this package out (it is never written), so loading it with default values can't ship anything. */
	bool IsLeftOutOfCook(FName PackageName)
	{
		FScopeLock Lock(&GLock);
		if (GLeftOutOfCook.Contains(PackageName))
		{
			return true;
		}
		ReadNeverCookRootsLocked();
		const FString Name = PackageName.ToString() + TEXT("/");
		for (const FString& Root : GNeverCookRoots)
		{
			if (Name.StartsWith(Root, ESearchCase::IgnoreCase))
			{
				return true;
			}
		}
		return false;
	}

	class FZeroFillLoader;
	TMap<FLinkerLoad*, FZeroFillLoader*> GZeroFillLoaders;

	UObject* SerializedObjectOf(FLinkerLoad& Linker)
	{
		FUObjectSerializeContext* Context = static_cast<FArchive&>(Linker).GetSerializeContext();
		return Context ? Context->SerializedObject : nullptr;
	}

	/**
	 * Stands in for a linker's loader while the rest of a damaged object is skipped: reads give zeros (null references,
	 * empty arrays and strings, unset values) until the linker seeks away for good. Loads of other exports that start
	 * in the middle are read normally, and skipping resumes when they seek back.
	 */
	class FZeroFillLoader final : public FArchive
	{
	public:
		FZeroFillLoader(FLinkerLoad& InLinker, FArchive* InInner)
			: Linker(InLinker)
			, Inner(InInner)
		{
			SetIsLoading(true);
			SetIsPersistent(true);
		}

		virtual ~FZeroFillLoader()
		{
			// Only reached when the linker destroys its loader while skipping (otherwise Uninstall took the real one back).
			FScopeLock Lock(&GLock);
			GZeroFillLoaders.Remove(&Linker);
			delete Inner;
		}

		void Skip(int64 Position, UObject* Object)
		{
			FFrame& Frame = Frames.AddDefaulted_GetRef();
			Frame.Object = Object;
			Frame.Position = Position;
			Frame.bSkipping = true;
		}

		bool IsSkipping() const
		{
			return Frames.Num() > 0 && Frames.Last().bSkipping;
		}

		virtual void Serialize(void* Data, int64 Length) override
		{
			if (IsSkipping())
			{
				if (Data && Length > 0)
				{
					FMemory::Memzero(Data, Length);
				}
				Frames.Last().Position += FMath::Max<int64>(Length, 0);
				return;
			}
			Inner->Serialize(Data, Length);
		}

		virtual int64 Tell() override
		{
			return IsSkipping() ? Frames.Last().Position : Inner->Tell();
		}

		virtual void Seek(int64 Position) override
		{
			UObject* Serialized = SerializedObjectOf(Linker);
			if (IsSkipping())
			{
				FFrame& Top = Frames.Last();
				if (Top.Object && Serialized == Top.Object)
				{
					// Another export starts loading while the damaged one is still being read: read it for real.
					Top.ResumePosition = Top.Position;
					Top.bSkipping = false;
					Inner->Seek(Position);
					return;
				}
				// The damaged object is done.
				Frames.Pop(false);
				if (Frames.Num() == 0)
				{
					Uninstall(Position);
					return;
				}
			}
			FFrame& Top = Frames.Last();
			if (Top.ResumePosition != INDEX_NONE && Position == Top.ResumePosition && Serialized == Top.Object)
			{
				// Back from the nested load: keep skipping the damaged object.
				Top.bSkipping = true;
				Top.Position = Position;
				Top.ResumePosition = INDEX_NONE;
				return;
			}
			Inner->Seek(Position);
		}

		virtual int64 TotalSize() override { return Inner->TotalSize(); }
		virtual bool Precache(int64 Offset, int64 Size) override { return Inner->Precache(Offset, Size); }
		virtual void FlushCache() override { Inner->FlushCache(); }
		virtual void Flush() override { Inner->Flush(); }
		virtual bool Close() override { return Inner->Close(); }
		virtual FString GetArchiveName() const override { return Inner->GetArchiveName(); }

		bool bWasAsyncLoader = false;

	private:
		struct FFrame
		{
			UObject* Object = nullptr;
			int64 Position = 0;
			int64 ResumePosition = INDEX_NONE;
			bool bSkipping = false;
		};

		void Uninstall(int64 Position)
		{
			{
				FScopeLock Lock(&GLock);
				GZeroFillLoaders.Remove(&Linker);
			}
			LoaderOf(Linker) = Inner;
			Linker.bIsAsyncLoader = bWasAsyncLoader;
			FArchive* RealLoader = Inner;
			Inner = nullptr;
			RealLoader->Seek(Position);
			delete this;
		}

		FLinkerLoad& Linker;
		FArchive* Inner;
		TArray<FFrame, TInlineAllocator<2>> Frames;
	};

	FZeroFillLoader* FindZeroFill(FLinkerLoad* Linker)
	{
		if (!Linker)
		{
			return nullptr;
		}
		FScopeLock Lock(&GLock);
		FZeroFillLoader** Found = GZeroFillLoaders.Find(Linker);
		return Found && LoaderOf(*Linker) == *Found ? *Found : nullptr;
	}

	/** Makes the linker hand out zeros for the rest of the object being serialized (until it seeks away). */
	bool SkipRestOfObject(FLinkerLoad& Linker, int64 Position, UObject* Object)
	{
		FArchive*& Loader = LoaderOf(Linker);
		if (!Loader)
		{
			return false;
		}
		FZeroFillLoader* Wrapper = FindZeroFill(&Linker);
		if (!Wrapper)
		{
			Wrapper = new FZeroFillLoader(Linker, Loader);
			// GetAsyncLoader() casts the loader to FAsyncArchive; it must not see the wrapper.
			Wrapper->bWasAsyncLoader = Linker.bIsAsyncLoader;
			Linker.bIsAsyncLoader = false;
			Loader = Wrapper;
			FScopeLock Lock(&GLock);
			GZeroFillLoaders.Add(&Linker, Wrapper);
		}
		Wrapper->Skip(Position, Object);
		return true;
	}

	struct FHeaderCheck
	{
		uint32 NativeSlots = 0;
		uint32 SavedSlots = 0;
		bool bUnreadable = false;
	};

	/**
	 * Reads the unversioned header (16-bit skip/keep fragments) without consuming it. False when it refers to more
	 * property slots than Struct has (the engine would index past its property list) or makes no sense.
	 *
	 * The header is read through the linker itself, never through Ar: the archive the engine hands the properties is not
	 * always the linker. A native Serialize(FArchive&) that loads a nested struct (FNiagaraVariableBase, for one) gets an
	 * FArchiveFromStructuredArchive, which in a binary package passes reads, Tell and Seek on to the linker but asserts
	 * on TotalSize() (that assert crashed a cook).
	 */
	bool CheckHeader(const UStruct* Struct, FArchive& Ar, FLinkerLoad& Linker, FHeaderCheck& Out)
	{
		FArchive& File = Linker;
		const int64 Start = File.Tell();
		if (Start < 0 || Ar.Tell() != Start)
		{
			return true;   // not reading straight from this linker's file: as before
		}
		const int64 Size = File.TotalSize();
		if (Size <= 0 || Start > Size)
		{
			return true;   // not a seekable archive: as before
		}
		for (FProperty* Property = Struct->PropertyLink; Property; Property = Property->PropertyLinkNext)
		{
			if (!Property->IsEditorOnlyProperty())
			{
				Out.NativeSlots += uint32(FMath::Max(Property->ArrayDim, 1));
			}
		}
		uint32 Running = 0;
		int64 Position = Start;
		bool bLast = false;
		bool bOverflow = false;
		const uint32 MaxFragments = Out.NativeSlots + 2;
		for (uint32 Index = 0; Index < MaxFragments && !bLast; ++Index)
		{
			if (Position + 2 > Size)
			{
				Out.bUnreadable = true;
				break;
			}
			uint16 Packed = 0;
			File << Packed;
			Position += 2;
			if (File.IsError())
			{
				Out.bUnreadable = true;
				break;
			}
			const uint32 SkipNum = Packed & 0x7Fu;
			const uint32 ValueNum = Packed >> 9;
			bLast = (Packed & 0x100u) != 0;
			if (SkipNum == 0 && ValueNum == 0 && !bLast)
			{
				Out.bUnreadable = true;   // the engine never writes an empty fragment before the last one
				break;
			}
			Running += SkipNum + ValueNum;
			if (ValueNum > 0)
			{
				Out.SavedSlots = Running;
			}
			if (Running > Out.NativeSlots && (ValueNum > 0 || !bLast))
			{
				Out.SavedSlots = FMath::Max(Out.SavedSlots, Running);
				bOverflow = true;
				break;
			}
		}
		if (!bLast && !bOverflow && !Out.bUnreadable)
		{
			Out.bUnreadable = true;
		}
		File.Seek(Start);
		return !Out.bUnreadable && !bOverflow;
	}

	FString DescribeDamage(FName PackageName, const UStruct* Struct, UObject* Object, const FHeaderCheck& Check)
	{
		const FString ObjectName = Object ? Object->GetPathName() : PackageName.ToString();
		return Check.bUnreadable
			? FString::Printf(TEXT("%s: the saved %s properties could not be read (the data does not match this project's class)"),
				*ObjectName, *Struct->GetName())
			: FString::Printf(TEXT("%s: saved with %u %s property slots, but this project's %s has %u"),
				*ObjectName, Check.SavedSlots, *Struct->GetName(), *Struct->GetPathName(), Check.NativeSlots);
	}

	void Report(FName PackageName, const FString& Details, const UStruct* Struct)
	{
		bool bFirst = false;
		{
			FScopeLock Lock(&GLock);
			if (!GDamaged.Contains(PackageName))
			{
				GDamaged.Add(PackageName, Details);
			}
			const FString Key = PackageName.ToString() + TEXT("|") + Struct->GetPathName();
			if (!GReported.Contains(Key))
			{
				GReported.Add(Key);
				bFirst = true;
			}
		}
		if (bFirst && GCookMode)
		{
			UE_LOG(LogRebirthSafeLoad, Warning, TEXT("%s. The rest of it loads with default values; this cook leaves the package out, so nothing of it is packaged ")
				TEXT("(the game uses its own)."), *Details);
		}
		else if (bFirst)
		{
			UE_LOG(LogRebirthSafeLoad, Warning, TEXT("%s. The rest of it loads with default values instead of crashing the editor. ")
				TEXT("Don't Make Editable or re-save this package; the End project's class needs the game's properties first."), *Details);
		}
	}

	void HookedSerializeUnversionedProperties(const UStruct* Struct, FStructuredArchive::FSlot Slot, uint8* Data, UStruct* DefaultsStruct, uint8* DefaultsData)
	{
		FArchive& Ar = Slot.GetUnderlyingArchive();
		// Only loads from a package file are checked (cooked game objects come through a linker); anything else (memory
		// readers, duplication, text assets) loads exactly as without the guard.
		FLinkerLoad* Linker = Struct && Ar.IsLoading() && !Ar.IsTextFormat() ? Cast<FLinkerLoad>(Ar.GetLinker()) : nullptr;
		if (Linker)
		{
			if (FZeroFillLoader* ZeroFill = FindZeroFill(Linker))
			{
				if (ZeroFill->IsSkipping())
				{
					// Inside a damaged object that is being skipped: there is nothing to read.
					Slot.EnterRecord();
					return;
				}
			}
			if (Ar.IsError())
			{
				Slot.EnterRecord();
				return;
			}
			FHeaderCheck Check;
			if (!CheckHeader(Struct, Ar, *Linker, Check))
			{
				UObject* Object = SerializedObjectOf(*Linker);
				const FName PackageName = Linker->LinkerRoot ? Linker->LinkerRoot->GetFName() : FName(TEXT("(unknown package)"));
				const FString Details = DescribeDamage(PackageName, Struct, Object, Check);
				if (GCookMode && !IsLeftOutOfCook(PackageName))
				{
					// This cook would write the package: with default values it would ship broken, and read as it is it
					// crashes. Stop with its name instead.
					UE_LOG(LogRebirthSafeLoad, Fatal, TEXT("%s. This cook would package it with default values, so the cook stops here. Leave it out of the cook ")
						TEXT("(Project Settings > Packaging > Directories To Never Cook, or don't reference it from what the mod packages), or give the End project's ")
						TEXT("class the game's properties."), *Details);
				}
				Slot.EnterRecord();
				Report(PackageName, Details, Struct);
				if (!SkipRestOfObject(*Linker, static_cast<FArchive&>(*Linker).Tell(), Object))
				{
					Ar.SetError();
				}
				return;
			}
		}
		GOriginal(Struct, Slot, Data, DefaultsStruct, DefaultsData);
	}

#if PLATFORM_WINDOWS
	void WriteAbsoluteJump(uint8* At, const void* To)
	{
		At[0] = 0xFF;   // jmp qword ptr [rip+0]
		At[1] = 0x25;
		At[2] = At[3] = At[4] = At[5] = 0;
		FMemory::Memcpy(At + 6, &To, sizeof(To));
	}

	uint8* FindTarget(FString& OutReason)
	{
		HMODULE Module = GetModuleHandleW(L"UE4Editor-CoreUObject.dll");
		if (!Module)
		{
			OutReason = TEXT("UE4Editor-CoreUObject.dll is not loaded (this is not the editor)");
			return nullptr;
		}
		uint8* Base = reinterpret_cast<uint8*>(Module);
		const IMAGE_DOS_HEADER* Dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(Base);
		const IMAGE_NT_HEADERS64* Nt = reinterpret_cast<const IMAGE_NT_HEADERS64*>(Base + Dos->e_lfanew);
		if (Nt->FileHeader.TimeDateStamp != ExpectedTimeDateStamp || Nt->OptionalHeader.SizeOfImage != ExpectedSizeOfImage)
		{
			OutReason = FString::Printf(TEXT("UE4Editor-CoreUObject.dll is not RebirthEngineV5's build (time stamp %08x, size %x)"),
				Nt->FileHeader.TimeDateStamp, Nt->OptionalHeader.SizeOfImage);
			return nullptr;
		}
		uint8* Target = Base + TargetRva;
		if (FMemory::Memcmp(Target, ExpectedPrologue, PrologueSize) != 0)
		{
			OutReason = TEXT("SerializeUnversionedProperties does not start as expected (already patched?)");
			return nullptr;
		}
		uint8 Hash[20];
		FSHA1::HashBuffer(Target, TargetSize, Hash);
		const FString HashText = BytesToHex(Hash, 20);
		if (!HashText.Equals(ExpectedSha1, ESearchCase::IgnoreCase))
		{
			OutReason = FString::Printf(TEXT("SerializeUnversionedProperties is not the expected code (SHA-1 %s)"), *HashText);
			return nullptr;
		}
		return Target;
	}

	void Install()
	{
		if (GActive)
		{
			return;
		}
		if (FParse::Param(FCommandLine::Get(), TEXT("NoRebirthSafeLoad")))
		{
			GInactiveReason = TEXT("-NoRebirthSafeLoad");
			UE_LOG(LogRebirthSafeLoad, Display, TEXT("Cooked-load guard is off: %s."), *GInactiveReason);
			return;
		}
		// A cook must never write an object that could not be read in full: in a cook the guard only stands in for
		// packages the cook leaves out (IsLeftOutOfCook); in other commandlets it stays off unless -RebirthSafeLoad is on
		// the command line (for batch tests that only load; it then guards everything, as in the editor).
		if (IsRunningCommandlet() && !FParse::Param(FCommandLine::Get(), TEXT("RebirthSafeLoad")))
		{
			if (!IsCookCommandlet())
			{
				GInactiveReason = TEXT("commandlet (add -RebirthSafeLoad to turn it on)");
				UE_LOG(LogRebirthSafeLoad, Display, TEXT("Cooked-load guard is off: %s."), *GInactiveReason);
				return;
			}
			GCookMode = true;
		}
		FString Reason;
		uint8* Target = FindTarget(Reason);
		if (!Target)
		{
			GInactiveReason = Reason;
			UE_LOG(LogRebirthSafeLoad, Display, TEXT("Cooked-load guard is off: %s."), *Reason);
			return;
		}
		uint8* Trampoline = static_cast<uint8*>(VirtualAlloc(nullptr, 64, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
		if (!Trampoline)
		{
			GInactiveReason = TEXT("no memory for the trampoline");
			UE_LOG(LogRebirthSafeLoad, Warning, TEXT("Cooked-load guard is off: %s."), *GInactiveReason);
			return;
		}
		FMemory::Memcpy(Trampoline, Target, PrologueSize);
		WriteAbsoluteJump(Trampoline + PrologueSize, Target + PrologueSize);
		FlushInstructionCache(GetCurrentProcess(), Trampoline, PrologueSize + JumpSize);

		DWORD OldProtect = 0;
		if (!VirtualProtect(Target, JumpSize, PAGE_EXECUTE_READWRITE, &OldProtect))
		{
			VirtualFree(Trampoline, 0, MEM_RELEASE);
			GInactiveReason = TEXT("the engine code could not be made writable");
			UE_LOG(LogRebirthSafeLoad, Warning, TEXT("Cooked-load guard is off: %s."), *GInactiveReason);
			return;
		}
		FMemory::Memcpy(GSavedBytes, Target, JumpSize);
		GOriginal = reinterpret_cast<FSerializeUnversionedFn>(Trampoline);
		WriteAbsoluteJump(Target, reinterpret_cast<const void*>(&HookedSerializeUnversionedProperties));
		DWORD Ignored = 0;
		VirtualProtect(Target, JumpSize, OldProtect, &Ignored);
		FlushInstructionCache(GetCurrentProcess(), Target, JumpSize);
		GTarget = Target;
		GActive = true;
		GInactiveReason.Empty();
		if (GCookMode)
		{
			UE_LOG(LogRebirthSafeLoad, Display, TEXT("Cooked-load guard is on for this cook: game packages it leaves out (Directories To Never Cook, the game's cooked copies) ")
				TEXT("load with default values when their saved properties don't fit this project's classes; any other such package stops the cook with its name."));
		}
		else
		{
			UE_LOG(LogRebirthSafeLoad, Display, TEXT("Cooked-load guard is on: cooked objects whose saved properties don't fit this project's classes load with default values instead of crashing the editor."));
		}
	}

	void Uninstall()
	{
		if (!GActive || !GTarget)
		{
			return;
		}
		{
			FScopeLock Lock(&GLock);
			if (GZeroFillLoaders.Num() > 0)
			{
				return;   // a package is still being read; leave the guard in place
			}
		}
		DWORD OldProtect = 0;
		if (VirtualProtect(GTarget, JumpSize, PAGE_EXECUTE_READWRITE, &OldProtect))
		{
			FMemory::Memcpy(GTarget, GSavedBytes, JumpSize);
			DWORD Ignored = 0;
			VirtualProtect(GTarget, JumpSize, OldProtect, &Ignored);
			FlushInstructionCache(GetCurrentProcess(), GTarget, JumpSize);
			GActive = false;
			GInactiveReason = TEXT("shut down");
			// The trampoline stays allocated: a thread could still be returning through it.
		}
	}
#else
	void Install() { GInactiveReason = TEXT("only for Windows"); }
	void Uninstall() {}
#endif

	void PrintStatus(const TArray<FString>& Args)
	{
		if (GActive)
		{
			UE_LOG(LogRebirthSafeLoad, Display, TEXT("Cooked-load guard is on%s."), GCookMode ? TEXT(" (cook: only for packages the cook leaves out)") : TEXT(""));
		}
		else
		{
			UE_LOG(LogRebirthSafeLoad, Display, TEXT("Cooked-load guard is off: %s."), *GInactiveReason);
		}
		FScopeLock Lock(&GLock);
		UE_LOG(LogRebirthSafeLoad, Display, TEXT("%d package(s) with objects that could not be read in full:"), GDamaged.Num());
		for (const TPair<FName, FString>& Entry : GDamaged)
		{
			UE_LOG(LogRebirthSafeLoad, Display, TEXT("  %s"), *Entry.Value);
		}
	}

	FAutoConsoleCommand GStatusCommand(
		TEXT("Rebirth.SafeLoad.Status"),
		TEXT("Shows whether the cooked-load guard is on and which packages it had to skip parts of."),
		FConsoleCommandWithArgsDelegate::CreateStatic(&PrintStatus));
}

namespace RebirthSafeLoad
{
	bool IsActive()
	{
		return RebirthSafeLoadPrivate::GActive;
	}

	FString GetInactiveReason()
	{
		return RebirthSafeLoadPrivate::GInactiveReason;
	}

	bool WasPackageDamaged(FName PackageName, FString* OutDetails)
	{
		using namespace RebirthSafeLoadPrivate;
		FScopeLock Lock(&GLock);
		const FString* Found = GDamaged.Find(PackageName);
		if (Found && OutDetails)
		{
			*OutDetails = *Found;
		}
		return Found != nullptr;
	}

	TArray<FName> GetDamagedPackages()
	{
		using namespace RebirthSafeLoadPrivate;
		FScopeLock Lock(&GLock);
		TArray<FName> Names;
		GDamaged.GetKeys(Names);
		return Names;
	}

	void AddPackagesLeftOutOfCook(const TArray<FName>& PackageNames)
	{
		using namespace RebirthSafeLoadPrivate;
		FScopeLock Lock(&GLock);
		GLeftOutOfCook.Append(PackageNames);
	}
}

class FRebirthSafeLoadModule : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		RebirthSafeLoadPrivate::Install();
	}

	virtual void ShutdownModule() override
	{
		RebirthSafeLoadPrivate::Uninstall();
	}
};

IMPLEMENT_MODULE(FRebirthSafeLoadModule, RebirthSafeLoad)
