#include "RebirthShaderLayoutDiagnosticsLibrary.h"

#include "Dom/JsonObject.h"
#include "Misc/SecureHash.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/MemoryLayout.h"

namespace RebirthShaderLayoutDiagnostics
{
	struct FSavedLayout
	{
		uint64 NameHash;
		uint32 Size;
		const TCHAR* Hash;
	};

	// Exact 98 dependencies from the original retail RM_Surface .uexp.
	// Material resource hash: 926c264f4c1d66242530b4dffbaf744532c51cfe.
	// .uexp SHA256: b81f62328d53b291d5731f73cb03a689e247d79e7f1081b604528e87c7008e91.
	static const FSavedLayout SavedLayouts[] = {
#include "RetailRM_SurfaceLayouts.inl"
	};
	static_assert(UE_ARRAY_COUNT(SavedLayouts) == 98, "Retail RM_Surface dependency table must remain complete.");

	static FString HashString(const FSHAHash& Hash)
	{
		return Hash.ToString().ToLower();
	}

	static TSharedRef<FJsonObject> LayoutParameters(const FPlatformTypeLayoutParameters& Layout)
	{
		TSharedRef<FJsonObject> Json = MakeShared<FJsonObject>();
		Json->SetNumberField(TEXT("flags"), Layout.Flags);
		Json->SetNumberField(TEXT("max_field_alignment"), Layout.MaxFieldAlignment);
		Json->SetBoolField(TEXT("with_editor_only"), Layout.WithEditorOnly());
		Json->SetBoolField(TEXT("with_ray_tracing"), Layout.WithRaytracing());
		Json->SetNumberField(TEXT("memory_image_pointer_bytes"), Layout.GetMemoryImagePointerSize());
		return Json;
	}
}

FString URebirthShaderLayoutDiagnosticsLibrary::GetRetailShaderLayoutDiagnostics()
{
	using namespace RebirthShaderLayoutDiagnostics;
	if (!IsInGameThread())
	{
		return TEXT("{\"error\":\"layout_diagnostics_require_game_thread\"}");
	}
	FPlatformTypeLayoutParameters CurrentLayout;
	CurrentLayout.InitializeForCurrent();
	FPlatformTypeLayoutParameters WindowsRuntimeLayout;
	WindowsRuntimeLayout.InitializeForPlatform(TEXT("Windows"), false);

	TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
	Root->SetStringField(TEXT("material_resource_hash"), TEXT("926c264f4c1d66242530b4dffbaf744532c51cfe"));
	Root->SetStringField(TEXT("source_uexp_sha256"), TEXT("b81f62328d53b291d5731f73cb03a689e247d79e7f1081b604528e87c7008e91"));
	Root->SetObjectField(TEXT("current_layout"), LayoutParameters(CurrentLayout));
	Root->SetObjectField(TEXT("windows_runtime_layout"), LayoutParameters(WindowsRuntimeLayout));
	Root->SetBoolField(TEXT("diagnostic_only"), true);
	Root->SetBoolField(TEXT("changes_loader_acceptance"), false);
	Root->SetStringField(TEXT("runtime_match_meaning"), TEXT("Known stripped runtime schema; requires source-layout-aware reconstruction before native editor access."));

	TArray<TSharedPtr<FJsonValue>> Dependencies;
	int32 UnknownTypes = 0;
	int32 MatchesCurrent = 0;
	int32 MatchesRuntime = 0;
	int32 MatchesBoth = 0;
	int32 MatchesNeither = 0;
	for (const FSavedLayout& Saved : SavedLayouts)
	{
		TSharedRef<FJsonObject> Entry = MakeShared<FJsonObject>();
		Entry->SetStringField(TEXT("name_hash"), FString::Printf(TEXT("%016llx"), static_cast<unsigned long long>(Saved.NameHash)));
		Entry->SetNumberField(TEXT("saved_size"), Saved.Size);
		Entry->SetStringField(TEXT("saved_hash"), Saved.Hash);
		const FTypeLayoutDesc* Type = FTypeLayoutDesc::Find(Saved.NameHash);
		Entry->SetBoolField(TEXT("registered"), Type != nullptr);
		if (!Type)
		{
			++UnknownTypes;
			Entry->SetStringField(TEXT("classification"), TEXT("unregistered_native_type"));
		}
		else
		{
			Entry->SetStringField(TEXT("native_type"), Type->Name);
			Entry->SetNumberField(TEXT("native_allocation_size"), Type->Size);
			FSHAHash CurrentHash;
			FSHAHash RuntimeHash;
			const uint32 CurrentSize = Freeze::HashLayout(*Type, CurrentLayout, CurrentHash);
			const uint32 RuntimeSize = Freeze::HashLayout(*Type, WindowsRuntimeLayout, RuntimeHash);
			const FString CurrentHashText = HashString(CurrentHash);
			const FString RuntimeHashText = HashString(RuntimeHash);
			const bool CurrentMatches = CurrentSize == Saved.Size && CurrentHashText.Equals(Saved.Hash, ESearchCase::IgnoreCase);
			const bool RuntimeMatches = RuntimeSize == Saved.Size && RuntimeHashText.Equals(Saved.Hash, ESearchCase::IgnoreCase);
			Entry->SetNumberField(TEXT("current_size"), CurrentSize);
			Entry->SetStringField(TEXT("current_hash"), CurrentHashText);
			Entry->SetNumberField(TEXT("windows_runtime_size"), RuntimeSize);
			Entry->SetStringField(TEXT("windows_runtime_hash"), RuntimeHashText);
			Entry->SetBoolField(TEXT("matches_current"), CurrentMatches);
			Entry->SetBoolField(TEXT("matches_windows_runtime"), RuntimeMatches);
			if (CurrentMatches && RuntimeMatches)
			{
				++MatchesBoth;
				Entry->SetStringField(TEXT("classification"), TEXT("matches_both"));
			}
			else if (CurrentMatches)
			{
				++MatchesCurrent;
				Entry->SetStringField(TEXT("classification"), TEXT("matches_current_editor"));
			}
			else if (RuntimeMatches)
			{
				++MatchesRuntime;
				Entry->SetStringField(TEXT("classification"), TEXT("matches_windows_runtime_requires_reconstruction"));
			}
			else
			{
				++MatchesNeither;
				Entry->SetStringField(TEXT("classification"), TEXT("differs_from_both_native_layouts"));
			}
		}
		Dependencies.Add(MakeShared<FJsonValueObject>(Entry));
	}
	Root->SetNumberField(TEXT("dependency_count"), Dependencies.Num());
	Root->SetNumberField(TEXT("unregistered_types"), UnknownTypes);
	Root->SetNumberField(TEXT("matches_current_only"), MatchesCurrent);
	Root->SetNumberField(TEXT("matches_windows_runtime_only"), MatchesRuntime);
	Root->SetNumberField(TEXT("matches_both"), MatchesBoth);
	Root->SetNumberField(TEXT("matches_neither"), MatchesNeither);
	Root->SetArrayField(TEXT("dependencies"), Dependencies);
	FString Result;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Result);
	if (!FJsonSerializer::Serialize(Root, Writer))
	{
		return TEXT("{\"error\":\"layout_diagnostic_json_serialization_failed\"}");
	}
	return Result;
}
