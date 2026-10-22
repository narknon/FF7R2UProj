#include "RebirthNiagaraVfx1LoadAdapter.h"
#include "CoreMinimal.h"
#include "NiagaraTypes.h"
#include "NiagaraVariant.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NiagaraCustomVersion.h"
#include "RebirthNiagaraVfx1Envelope.h"
#include "UObject/Class.h"
#include "UObject/UnrealType.h"
#include "UObject/UObjectThreadContext.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Package.h"
#include "Misc/CoreDelegates.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "Misc/ScopeLock.h"
#include "HAL/FileManager.h"
#include "HAL/IConsoleManager.h"
#include "HAL/PlatformProcess.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include <Windows.h>
#include "Windows/HideWindowsPlatformTypes.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"

// Niagara does not export these four methods in this engine. Their ordinary
// implementations below are copied exactly from NiagaraModule.cpp 1096-1172.
// They are a source-local ordinary fallback, not calls to unavailable exports.
FArchive& operator<<(FArchive& Ar, FNiagaraTypeDefinitionHandle& Handle)
{
    UScriptStruct* TypeDefStruct = FNiagaraTypeDefinition::StaticStruct();
    if (Ar.IsSaving())
    {
        FNiagaraTypeDefinition TypeDef = *Handle;
        TypeDefStruct->SerializeItem(Ar, &TypeDef, nullptr);
    }
    else if (Ar.IsLoading())
    {
        FNiagaraTypeDefinition TypeDef;
        TypeDefStruct->SerializeItem(Ar, &TypeDef, nullptr);
        Handle = FNiagaraTypeDefinitionHandle(TypeDef);
    }
    return Ar;
}

bool FNiagaraVariableBase::Serialize(FArchive& Ar)
{
    Ar.UsingCustomVersion(FNiagaraCustomVersion::GUID);
    const int32 NiagaraVersion = Ar.CustomVer(FNiagaraCustomVersion::GUID);
    if (!Ar.IsLoading() || NiagaraVersion >= FNiagaraCustomVersion::VariablesUseTypeDefRegistry)
    {
        Ar << Name;
        Ar << TypeDefHandle;
        if (NiagaraVersion >= FNiagaraCustomVersion::SQEXCustom1)
        {
            /*int32 unk;
            int32 unk2;
            int32 unk3;
            int32 unk4;
            Ar << unk;
            Ar << unk2;
            Ar << unk3;
            Ar << unk4;*/
        }
        return true;
    }
    return false;
}
#if WITH_EDITORONLY_DATA
void FNiagaraVariableBase::PostSerialize(const FArchive& Ar)
{
    if (Ar.IsLoading() && Ar.CustomVer(FNiagaraCustomVersion::GUID) < FNiagaraCustomVersion::VariablesUseTypeDefRegistry)
    {
        TypeDefHandle = FNiagaraTypeDefinitionHandle(TypeDef_DEPRECATED);
    }
}
#endif
bool FNiagaraVariable::Serialize(FArchive& Ar)
{
    FNiagaraVariableBase::Serialize(Ar);
    Ar.UsingCustomVersion(FNiagaraCustomVersion::GUID);
    const int32 NiagaraVersion = Ar.CustomVer(FNiagaraCustomVersion::GUID);
    if (!Ar.IsLoading() || NiagaraVersion >= FNiagaraCustomVersion::VariablesUseTypeDefRegistry)
    {
        if (NiagaraVersion >= FNiagaraCustomVersion::SQEXCustom1)
        {
            int32 unk = 0;
            int32 unk2 = 0;
            //int32 unk3 = 0;
            Ar << unk;
            Ar << unk2;
            //Ar << unk3;
        }
        Ar << VarData;
        if (NiagaraVersion >= FNiagaraCustomVersion::SQEXCustom1)
        {
            int32 unk3 = 0;
            Ar << unk3;
        }
        return true;
    }
    // loading legacy data
    return false;
}
#if WITH_EDITORONLY_DATA
void FNiagaraVariable::PostSerialize(const FArchive& Ar)
{
    FNiagaraVariableBase::PostSerialize(Ar);
}
#endif

DEFINE_LOG_CATEGORY_STATIC(LogRebirthNiagaraVfx1, Log, All);
namespace RebirthNiagaraVfx1LoadAdapter
{
namespace
{
    FCriticalSection StateLock;
    TSet<FName> LoadOnlyPackages;
    TArray<TSharedPtr<FJsonValue>> ReadRecords;
    uint64 SuccessfulReads = 0;
    uint64 RefusedReads = 0;
    uint64 RefusedSaves = 0;
    bool bInstalled = false;
    bool bRestored = false;
    bool bModulePinned = false;
    TWeakObjectPtr<UScriptStruct> BoundStruct;
    FArrayProperty* BoundVariableData = nullptr;
    UScriptStruct::ICppStructOps* OwnedOperations = nullptr;
    FDelegateHandle PreExitHandle;
    TUniquePtr<FAutoConsoleCommand> StateCommand;
    TUniquePtr<FAutoConsoleCommand> RetentionCommand;

    UObject* CurrentSerializedObject(FArchive& Ar)
    {
        FUObjectSerializeContext* Context = Ar.GetSerializeContext();
        if (!Context && !Ar.IsTextFormat())
        {
            // Structured binary proxies do not forward GetSerializeContext.
            // The public cacheable archive is the same data, but accept its
            // owner context only while the two archive cursors agree.
            FArchive* Cacheable = Ar.GetCacheableArchive();
            if (Cacheable && !Cacheable->IsTextFormat() && Cacheable->Tell() == Ar.Tell())
            {
                Context = Cacheable->GetSerializeContext();
            }
        }
        return Context ? Context->SerializedObject : nullptr;
    }

    bool RefusePersistentSave(FArchive& Ar, const FNiagaraVariable& Variable)
    {
        if (!Ar.IsSaving() || !Ar.IsPersistent()) { return false; }
        UObject* Object = CurrentSerializedObject(Ar);
        const FName PackageName = Object && Object->GetOutermost() ? Object->GetOutermost()->GetFName() : NAME_None;
        bool bSourcePackage = false;
        {
            FScopeLock Guard(&StateLock);
            bSourcePackage = !PackageName.IsNone() && LoadOnlyPackages.Contains(PackageName);
        }
        // Original VFX1 variables have an empty native TypeDefinition and an
        // opaque type hash. A duplicate with that unresolved type must not be
        // written by the ordinary serializer, which cannot preserve the hash.
        const bool bUnresolvedNamedVariable = !Variable.GetName().IsNone() && !Variable.GetType().IsValid();
        if (!bSourcePackage && !bUnresolvedNamedVariable) { return false; }
        {
            FScopeLock Guard(&StateLock);
            ++RefusedSaves;
        }
        UE_LOG(LogRebirthNiagaraVfx1, Error, TEXT("Refusing lossy persistent save/cook of load-only VFX1 or unresolved Niagara variable: %s [%s]"), *Variable.GetName().ToString(), *PackageName.ToString());
        Ar.SetError();
        return true;
    }

    struct FLoadOperations final : UScriptStruct::TCppStructOps<FNiagaraVariable>
    {
        using UScriptStruct::TCppStructOps<FNiagaraVariable>::Serialize;
        virtual bool Serialize(FArchive& Ar, void* Data) override
        {
            if (!Data) { Ar.SetError(); return true; }
            FNiagaraVariable& Variable = *static_cast<FNiagaraVariable*>(Data);
            if (RefusePersistentSave(Ar, Variable)) { return true; }
            Ar.UsingCustomVersion(FNiagaraCustomVersion::GUID);
            // Only actual SQEX persistent loading can use the recovered seam.
            if (!Ar.IsLoading() || Ar.IsSaving() || !Ar.IsPersistent() ||
                Ar.CustomVer(FNiagaraCustomVersion::GUID) != FNiagaraCustomVersion::SQEXCustom5)
            {
                return Variable.Serialize(Ar);
            }
            const int64 Start = Ar.Tell();
            if (!Variable.FNiagaraVariableBase::Serialize(Ar))
            {
                return false;
            }
            const int64 EnvelopeStart = Ar.Tell();
            RebirthNiagaraVfx1::FEnvelope Envelope;
            const auto Result = RebirthNiagaraVfx1::TryReadLoadOnlyEnvelope(Ar, Envelope);
            if (Result == RebirthNiagaraVfx1::EReadResult::NotVfx1)
            {
                // The helper restored its own prefix. Re-run the exact ordinary
                // source fallback from the complete variable start.
                Ar.Seek(Start);
                return Variable.Serialize(Ar);
            }
            if (Result == RebirthNiagaraVfx1::EReadResult::Refused || !BoundVariableData)
            {
                Ar.SetError();
                FScopeLock Guard(&StateLock);
                ++RefusedReads;
                return true;
            }
            UObject* Object = CurrentSerializedObject(Ar);
            UPackage* Package = Object ? Object->GetOutermost() : nullptr;
            if (!Object || !Package || Variable.GetName().IsNone() || Variable.GetType().IsValid())
            {
                // The proven source has a named variable, empty native type,
                // and a live serialized owner for its persistent-save fence.
                Ar.SetError();
                FScopeLock Guard(&StateLock);
                ++RefusedReads;
                return true;
            }
            TArray<uint8>* Destination = BoundVariableData->ContainerPtrToValuePtr<TArray<uint8>>(Data);
            if (!Destination) { Ar.SetError(); return true; }
            *Destination = MoveTemp(Envelope.VariableData);
            TSharedRef<FJsonObject> Row = MakeShared<FJsonObject>();
            Row->SetStringField(TEXT("archive"), Ar.GetArchiveName());
            Row->SetStringField(TEXT("object"), Object ? Object->GetPathName() : FString());
            Row->SetStringField(TEXT("package"), Package ? Package->GetName() : FString());
            Row->SetStringField(TEXT("variable_name"), Variable.GetName().ToString());
            Row->SetNumberField(TEXT("native_version"), Ar.CustomVer(FNiagaraCustomVersion::GUID));
            Row->SetNumberField(TEXT("start"), double(Start));
            Row->SetNumberField(TEXT("envelope_start"), double(EnvelopeStart));
            Row->SetNumberField(TEXT("end"), double(Ar.Tell()));
            Row->SetNumberField(TEXT("opaque_type_hash"), double(Envelope.OpaqueTypeHash));
            Row->SetNumberField(TEXT("format_word"), double(Envelope.FormatWord));
            Row->SetNumberField(TEXT("opaque_header_word"), double(Envelope.OpaqueHeaderWord));
            Row->SetNumberField(TEXT("variable_bytes"), Destination->Num());
            {
                FScopeLock Guard(&StateLock);
                ++SuccessfulReads;
                if (Package) { LoadOnlyPackages.Add(Package->GetFName()); }
                if (ReadRecords.Num() < 256) { ReadRecords.Add(MakeShared<FJsonValueObject>(Row)); }
            }
            return true;
        }
    };

    struct FOrdinaryOperations final : UScriptStruct::TCppStructOps<FNiagaraVariable>
    {
        using UScriptStruct::TCppStructOps<FNiagaraVariable>::Serialize;
        virtual bool Serialize(FArchive& Ar, void* Data) override
        {
            if (!Data) { Ar.SetError(); return true; }
            FNiagaraVariable& Variable = *static_cast<FNiagaraVariable*>(Data);
            if (RefusePersistentSave(Ar, Variable)) { return true; }
            return Variable.Serialize(Ar);
        }
    };

    bool PropertyFits(const FProperty* Property, const UStruct* Container)
    {
        return Property && Container && Property->ArrayDim == 1 && Property->ElementSize > 0 &&
            Property->GetOffset_ForInternal() >= 0 && Container->GetStructureSize() >= Property->ElementSize &&
            Property->GetOffset_ForInternal() <= Container->GetStructureSize() - Property->ElementSize;
    }

    FStructProperty* RetainedStructProperty(UStruct* Container, const TCHAR* Name, const TCHAR* ExactStructPath)
    {
        FStructProperty* Property = FindFProperty<FStructProperty>(Container, Name);
        return PropertyFits(Property, Container) && Property->Struct && Property->Struct->GetPathName() == ExactStructPath &&
            Property->ElementSize == Property->Struct->GetStructureSize() ? Property : nullptr;
    }

    void InspectRetention(const TArray<FString>& Args)
    {
        // This reads only an already-loaded notify in an owned read-only test.
        // It does not load assets, dispatch notifies, mutate values, or save packages.
        if (!IsInGameThread() || !FParse::Param(FCommandLine::Get(), TEXT("RebirthRawAnimationLoadProbe"))) { return; }
        TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
        Root->SetNumberField(TEXT("schema_version"), 1);
        Root->SetNumberField(TEXT("process_id"), FPlatformProcess::GetCurrentProcessId());
        Root->SetBoolField(TEXT("success"), false);
        Root->SetStringField(TEXT("object_path"), Args.Num() == 1 ? Args[0] : FString());
        FString Error;
        auto Inspect = [&]() -> bool
        {
            if (!bInstalled || !BoundVariableData || Args.Num() != 1 || Args[0].Len() > 1024)
            { Error = TEXT("Adapter/argument scope is invalid."); return false; }
            UObject* Object = FindObject<UObject>(nullptr, *Args[0]);
            if (!IsValid(Object) || Object->GetPathName() != Args[0] ||
                Object->GetClass()->GetPathName() != TEXT("/Script/EndGame.AnimNotifyState_EndTimedNiagaraEffect") ||
                Object->HasAnyFlags(RF_NeedLoad|RF_NeedPostLoad|RF_BeginDestroyed|RF_FinishDestroyed))
            { Error = TEXT("Exact fully loaded native EndTimedNiagara notify not found."); return false; }
            UAnimSequence* Animation = Cast<UAnimSequence>(Object->GetOuter());
            if (!IsValid(Animation) || Animation->HasAnyFlags(RF_NeedLoad|RF_NeedPostLoad|RF_BeginDestroyed|RF_FinishDestroyed) || Animation->Notifies.Num() < 0 || Animation->Notifies.Num() > 4096)
            { Error = TEXT("Loaded animation owner is invalid."); return false; }
            bool bOwnedNotify = false;
            for (const FAnimNotifyEvent& Event : Animation->Notifies) { bOwnedNotify |= Event.NotifyStateClass == Object; }
            if (!bOwnedNotify) { Error = TEXT("Notify is not retained in the exact owner's native notify events."); return false; }
            Root->SetStringField(TEXT("owner_animation"), Animation->GetPathName());
            Root->SetStringField(TEXT("object_class"), Object->GetClass()->GetPathName());
            FStructProperty* Create = RetainedStructProperty(Object->GetClass(), TEXT("m_NiagaraCreateParams"), TEXT("/Script/EndGame.EndNiagaraCreateParams"));
            FStructProperty* Info = Create ? RetainedStructProperty(Create->Struct, TEXT("m_NiagaraParameterInfo"), TEXT("/Script/VFXNiagara.VFXNiagaraParameterInfo")) : nullptr;
            FArrayProperty* Users = Info ? FindFProperty<FArrayProperty>(Info->Struct, TEXT("m_UserParams")) : nullptr;
            FStructProperty* User = Users ? CastField<FStructProperty>(Users->Inner) : nullptr;
            if (!Create || !Info || !PropertyFits(Users, Info->Struct) || Users->ElementSize != sizeof(TArray<uint8>) ||
                !User || User->ArrayDim != 1 || User->GetOffset_ForInternal() != 0 || !User->Struct ||
                User->Struct->GetPathName() != TEXT("/Script/VFXNiagara.VFXNiagaraUserParameter") || User->ElementSize != User->Struct->GetStructureSize())
            { Error = TEXT("Native retained parameter property schema does not match."); return false; }
            FStructProperty* VariableProperty = RetainedStructProperty(User->Struct, TEXT("m_Variable"), TEXT("/Script/Niagara.NiagaraVariable"));
            FStructProperty* VariantProperty = RetainedStructProperty(User->Struct, TEXT("m_Variant"), TEXT("/Script/Niagara.NiagaraVariant"));
            FArrayProperty* VariantBytes = VariantProperty ? FindFProperty<FArrayProperty>(VariantProperty->Struct, TEXT("Bytes")) : nullptr;
            if (!VariableProperty || VariableProperty->Struct != FNiagaraVariable::StaticStruct() || VariableProperty->ElementSize != sizeof(FNiagaraVariable) ||
                !VariantProperty || VariantProperty->Struct != FNiagaraVariant::StaticStruct() || VariantProperty->ElementSize != sizeof(FNiagaraVariant) ||
                !PropertyFits(VariantBytes, VariantProperty->Struct) || VariantBytes->GetOwnerStruct() != VariantProperty->Struct ||
                VariantBytes->ElementSize != sizeof(TArray<uint8>) || !CastField<FByteProperty>(VariantBytes->Inner) || VariantBytes->Inner->ElementSize != 1 ||
                VariantBytes->Inner->ArrayDim != 1 || VariantBytes->Inner->GetOffset_ForInternal() != 0)
            { Error = TEXT("Native variable/variant schema does not match."); return false; }
            void* CreateData = Create->ContainerPtrToValuePtr<void>(Object);
            void* InfoData = Info->ContainerPtrToValuePtr<void>(CreateData);
            FScriptArrayHelper Parameters(Users, Users->ContainerPtrToValuePtr<void>(InfoData));
            if (Parameters.Num() < 0 || Parameters.Num() > 4096)
            { Error = TEXT("Retained parameter count exceeds the owned bound."); return false; }
            TArray<TSharedPtr<FJsonValue>> Rows;
            int64 TotalBytes = 0;
            constexpr int64 MaximumBytes = 1024 * 1024;
            for (int32 Index = 0; Index < Parameters.Num(); ++Index)
            {
                uint8* Parameter = Parameters.GetRawPtr(Index);
                const FNiagaraVariable* Variable = VariableProperty->ContainerPtrToValuePtr<FNiagaraVariable>(Parameter);
                const FNiagaraVariant* Variant = VariantProperty->ContainerPtrToValuePtr<FNiagaraVariant>(Parameter);
                const TArray<uint8>* Bytes = VariantBytes->ContainerPtrToValuePtr<TArray<uint8>>(Variant);
                const int64 VariableBytes = Variable->GetAllocatedSizeInBytes();
                const int64 FollowingBytes = Bytes->Num();
                if (VariableBytes < 0 || FollowingBytes < 0 || VariableBytes > MaximumBytes || FollowingBytes > MaximumBytes ||
                    VariableBytes + FollowingBytes > MaximumBytes - TotalBytes || (VariableBytes > 0 && !Variable->GetData()) || (FollowingBytes > 0 && !Bytes->GetData()))
                { Error = TEXT("Retained parameter byte count exceeds the owned aggregate bound."); return false; }
                TotalBytes += VariableBytes + FollowingBytes;
                TSharedRef<FJsonObject> Row = MakeShared<FJsonObject>();
                Row->SetStringField(TEXT("name"), Variable->GetName().ToString());
                Row->SetStringField(TEXT("variable_data_hex"), BytesToHex(Variable->GetData(), static_cast<int32>(VariableBytes)).ToLower());
                Row->SetStringField(TEXT("variant_bytes_hex"), BytesToHex(Bytes->GetData(), static_cast<int32>(FollowingBytes)).ToLower());
                Row->SetNumberField(TEXT("variant_mode"), static_cast<int32>(Variant->GetMode()));
                Rows.Add(MakeShared<FJsonValueObject>(Row));
            }
            Root->SetArrayField(TEXT("params"), Rows);
            Root->SetNumberField(TEXT("inspected_total_bytes"), double(TotalBytes));
            return true;
        };
        Root->SetBoolField(TEXT("success"), Inspect());
        Root->SetStringField(TEXT("error"), Error);
        FString Text;
        FJsonSerializer::Serialize(Root, TJsonWriterFactory<>::Create(&Text));
        const FString Directory = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("AnimationLoadAdapter"));
        IFileManager::Get().MakeDirectory(*Directory, true);
        FFileHelper::SaveStringToFile(Text, *FPaths::Combine(Directory, TEXT("LatestRetention.json")));
    }

    void WriteState()
    {
        TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
        Root->SetNumberField(TEXT("schema_version"), 1);
        Root->SetNumberField(TEXT("process_id"), FPlatformProcess::GetCurrentProcessId());
        {
            FScopeLock Guard(&StateLock);
            Root->SetBoolField(TEXT("installed"), bInstalled);
            Root->SetBoolField(TEXT("ordinary_operations_restored"), bRestored);
            Root->SetBoolField(TEXT("owning_code_module_pinned_until_process_exit"), bModulePinned);
            Root->SetNumberField(TEXT("successful_loads"), double(SuccessfulReads));
            Root->SetNumberField(TEXT("refused_loads"), double(RefusedReads));
            Root->SetNumberField(TEXT("refused_persistent_saves"), double(RefusedSaves));
            Root->SetArrayField(TEXT("loads"), ReadRecords);
        }
        Root->SetBoolField(TEXT("opaque_type_semantics_recovered"), false);
        Root->SetBoolField(TEXT("lossless_vfx1_writer_implemented"), false);
        FString Text;
        FJsonSerializer::Serialize(Root, TJsonWriterFactory<>::Create(&Text));
        const FString Directory = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("AnimationLoadAdapter"));
        IFileManager::Get().MakeDirectory(*Directory, true);
        FFileHelper::SaveStringToFile(Text, *FPaths::Combine(Directory, TEXT("LatestState.json")));
    }
}

void Startup()
{
    check(IsInGameThread());
    if (bInstalled) { return; }
    FlushAsyncLoading();
    UScriptStruct* Struct = FNiagaraVariable::StaticStruct();
    Struct->PrepareCppStructOps();
    UScriptStruct::ICppStructOps* Existing = Struct->GetCppStructOps();
    FArrayProperty* Array = FindFProperty<FArrayProperty>(Struct, TEXT("VarData"));
    checkf(Existing && Existing->GetSize() == sizeof(FNiagaraVariable) && Existing->GetAlignment() == alignof(FNiagaraVariable) &&
        Struct->GetStructureSize() == sizeof(FNiagaraVariable) && Existing->HasSerializer() && !Existing->HasStructuredSerializer() &&
        Array && Array->GetOwnerStruct() == Struct && CastField<FByteProperty>(Array->Inner) && Array->ArrayDim == 1 &&
        Array->ElementSize == sizeof(TArray<uint8>) && Array->GetOffset_ForInternal() >= 0 &&
        Array->GetOffset_ForInternal() <= int32(sizeof(FNiagaraVariable) - sizeof(TArray<uint8>)),
        TEXT("Niagara variable native layout/serialization operations do not match the reviewed adapter"));
    BoundVariableData = Array;
    BoundStruct = Struct;
    // Both the adapter and restored ordinary mirror have virtual functions in
    // this DLL. Protect even an explicit non-shutdown UnloadModule(false), which
    // ignores SupportsDynamicReloading and otherwise calls FreeDllHandle.
    HMODULE PinnedModule = nullptr;
    bModulePinned = GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_PIN,
        reinterpret_cast<LPCWSTR>(&Startup), &PinnedModule) != 0 && PinnedModule != nullptr;
    checkf(bModulePinned, TEXT("Cannot pin the owning Niagara struct-ops code for its process lifetime"));
    Struct->ClearCppStructOps();
    OwnedOperations = new FLoadOperations();
    UScriptStruct::DeferCppStructOps(Struct->GetFName(), OwnedOperations);
    Struct->PrepareCppStructOps();
    check(Struct->GetCppStructOps() == OwnedOperations);
    bInstalled = true;
    bRestored = false;
    PreExitHandle = FCoreDelegates::OnPreExit.AddStatic(&Shutdown);
    StateCommand = MakeUnique<FAutoConsoleCommand>(TEXT("Rebirth.NiagaraVfx1State"), TEXT("Snapshot load-only VFX1 adapter diagnostics to Saved/AnimationLoadAdapter/LatestState.json"), FConsoleCommandDelegate::CreateStatic(&WriteState));
    RetentionCommand = MakeUnique<FAutoConsoleCommand>(TEXT("Rebirth.NiagaraVfx1Inspect"), TEXT("Owned read-only retention inspection of an already-loaded native notify."), FConsoleCommandWithArgsDelegate::CreateStatic(&InspectRetention));
    UE_LOG(LogRebirthNiagaraVfx1, Display, TEXT("Registered bounded VFX1 load adapter; opaque source saves/cooks are refused."));
}

void Shutdown()
{
    check(IsInGameThread());
    if (!bInstalled) { return; }
    FCoreDelegates::OnPreExit.Remove(PreExitHandle);
    StateCommand.Reset();
    RetentionCommand.Reset();
    if (UObjectInitialized())
    {
        // Struct operations may be active on the asynchronous loading thread.
        // Complete those calls before deleting their registry-owned vtable.
        FlushAsyncLoading();
        if (UScriptStruct* Struct = BoundStruct.Get())
        {
            // Refuse to replace operations registered later by another owner.
            if (Struct->GetCppStructOps() == OwnedOperations)
            {
                Struct->ClearCppStructOps();
                // Keep the required load-only source save fence after an explicit
                // module unload, while removing the actual load adaptation.
                UScriptStruct::DeferCppStructOps(Struct->GetFName(), new FOrdinaryOperations());
                Struct->PrepareCppStructOps();
                bRestored = true;
            }
        }
    }
    bInstalled = false;
    OwnedOperations = nullptr;
    BoundVariableData = nullptr;
    BoundStruct.Reset();
    // ModuleManager automatic shutdown deliberately abandons the DLL in memory
    // (ModuleManager.cpp609-616,730-731). Dynamic reload is already disabled by
    // the owning preview module; the restored source-local ops remain resident.
}
}
