#include "RebirthSkeletonCompatibilityEditorLibrary.h"
#include "Animation/RebirthSkeletonCompatibility.h"
#include "Animation/Skeleton.h"
#include "Components/SkeletalMeshComponent.h"
#include "ContentBrowserDelegates.h"
#include "ContentBrowserModule.h"
#include "Dom/JsonObject.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/Engine.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "HAL/FileManager.h"
#include "Misc/CoreDelegates.h"
#include "Misc/CommandLine.h"
#include "Misc/FileHelper.h"
#include "Misc/MessageDialog.h"
#include "Misc/Paths.h"
#include "Misc/PackageName.h"
#include "Misc/Parse.h"
#include "Modules/ModuleManager.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "UObject/GarbageCollection.h"
#include "UObject/GCObject.h"
#include "UObject/StrongObjectPtr.h"
#include "UObject/UObjectIterator.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthSkeletonCompatibilityEditor, Log, All);

namespace
{
    constexpr int32 MaxRegisteredPairs = 32;
    constexpr int64 MaxManifestBytes = 1024 * 1024;
    struct FRegisteredPair
    {
        FString SourcePath, TargetPath, SourceGuid, TargetGuid;
        int32 SourceBones = 0, TargetBones = 0;
        USkeleton* Source = nullptr;
        USkeleton* Target = nullptr;
    };

    class FRegisteredPairOwner final : public FGCObject
    {
    public:
        TArray<FRegisteredPair> Pairs;
        virtual void AddReferencedObjects(FReferenceCollector& Collector) override
        {
            for (FRegisteredPair& Pair : Pairs)
            {
                Collector.AddReferencedObject(Pair.Source);
                Collector.AddReferencedObject(Pair.Target);
            }
        }
        virtual FString GetReferencerName() const override { return TEXT("RebirthRegisteredSkeletonCompatibilityPairs"); }
    };

    TUniquePtr<FRegisteredPairOwner> PairOwner;
    FDelegateHandle MenuExtenderHandle;
    FDelegateHandle PostEngineInitHandle;
    FDelegateHandle OwnerPreExitHandle;
    bool bMutationInProgress = false;
    bool bManifestLoaded = false;
    FString ManifestPath() { return FPaths::ProjectConfigDir() / TEXT("RebirthCompatibleSkeletons.json"); }

    bool MayEdit(FString& OutDiagnostic)
    {
        if (!IsInGameThread() || IsGarbageCollecting())
        {
            OutDiagnostic = TEXT("Compatibility changes require the game thread outside garbage collection.");
            return false;
        }
        if (!PairOwner.IsValid())
        {
            PairOwner = MakeUnique<FRegisteredPairOwner>();
            // Direct commandlet/NullRHI API callers do not enter the UI module Startup.
            // Their roots must still be released before StaticExit's UObject purge.
            OwnerPreExitHandle = FCoreDelegates::OnPreExit.AddStatic(&RebirthSkeletonCompatibilityEditor::Shutdown);
        }
        return true;
    }

    struct FScopedMutation
    {
        bool bAcquired = false;
        explicit FScopedMutation(FString& OutDiagnostic)
        {
            if (!MayEdit(OutDiagnostic)) { return; }
            if (bMutationInProgress)
            { OutDiagnostic = TEXT("Compatibility mutation is already in progress; callback reentry was refused."); return; }
            bMutationInProgress = bAcquired = true;
        }
        ~FScopedMutation() { if (bAcquired) { bMutationInProgress = false; } }
    };

    // Finish actual component evaluation before changing registration or releasing roots.
    bool FenceComponents(const USkeleton* A, const USkeleton* B, FString& OutDiagnostic)
    {
        if (!MayEdit(OutDiagnostic)) { return false; }
        for (int32 Pass = 0; Pass < 8; ++Pass)
        {
            TArray<TWeakObjectPtr<USkeletalMeshComponent>> Components;
            for (TObjectIterator<USkeletalMeshComponent> It; It; ++It)
            {
                USkeletalMeshComponent* Component = *It;
                if (!IsValid(Component) || !Component->SkeletalMesh) { continue; }
                const USkeleton* Receiving = Component->SkeletalMesh->Skeleton;
                if ((Receiving == A || Receiving == B) && Component->IsRunningParallelEvaluation())
                { Components.Add(Component); }
            }
            if (Components.Num() == 0)
            {
                if ((A && !IsValid(A)) || (B && !IsValid(B)))
                { OutDiagnostic = TEXT("A skeleton became unavailable while completing animation tasks."); return false; }
                return true;
            }
            for (const auto& WeakComponent : Components)
            {
                USkeletalMeshComponent* Component = WeakComponent.Get();
                if (!IsValid(Component)) { continue; }
                Component->HandleExistingParallelEvaluationTask(true, true);
                // Completion can dispatch events that destroy or create components.
                // Re-snapshot on the next bounded pass instead of retaining an iterator.
            }
        }
        OutDiagnostic = TEXT("Affected animation tasks restarted during the bounded fence; registration was refused.");
        return false;
    }

    bool SamePair(const FRegisteredPair& Pair, const FString& A, const FString& B)
    {
        return (Pair.SourcePath == A && Pair.TargetPath == B) || (Pair.SourcePath == B && Pair.TargetPath == A);
    }

    bool ReadManifest(TArray<FRegisteredPair>& OutPairs, FString& OutDiagnostic)
    {
        OutPairs.Reset();
        const FString Path = ManifestPath();
        if (!IFileManager::Get().FileExists(*Path)) { return true; }
        const int64 Bytes = IFileManager::Get().FileSize(*Path);
        if (Bytes < 0 || Bytes > MaxManifestBytes) { OutDiagnostic = TEXT("Compatibility manifest exceeds its size limit."); return false; }
        FString Text;
        if (!FFileHelper::LoadFileToString(Text, *Path)) { OutDiagnostic = TEXT("Could not read compatibility manifest."); return false; }
        TSharedPtr<FJsonObject> Root;
        if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text), Root) || !Root.IsValid())
        { OutDiagnostic = TEXT("Compatibility manifest is invalid JSON; it was preserved."); return false; }
        double Schema = 0;
        const TArray<TSharedPtr<FJsonValue>>* Records = nullptr;
        FString Policy;
        if (!Root->TryGetNumberField(TEXT("schema_version"), Schema) || Schema != 1 ||
            !Root->TryGetStringField(TEXT("mapping_policy"), Policy) || Policy != TEXT("kh3_same_name_local_pose") ||
            !Root->TryGetArrayField(TEXT("pairs"), Records) || Records->Num() > MaxRegisteredPairs)
        { OutDiagnostic = TEXT("Unsupported compatibility manifest schema or pair limit; it was preserved."); return false; }
        for (const auto& Value : *Records)
        {
            if (!Value.IsValid() || Value->Type != EJson::Object)
            { OutDiagnostic = TEXT("Compatibility manifest contains a non-object pair; it was preserved."); return false; }
            const TSharedPtr<FJsonObject> Record = Value->AsObject();
            FRegisteredPair Pair;
            double SourceBones = 0, TargetBones = 0;
            if (!Record.IsValid() ||
                !Record->TryGetStringField(TEXT("source_skeleton"), Pair.SourcePath) ||
                !Record->TryGetStringField(TEXT("target_skeleton"), Pair.TargetPath) ||
                !Record->TryGetStringField(TEXT("source_guid"), Pair.SourceGuid) ||
                !Record->TryGetStringField(TEXT("target_guid"), Pair.TargetGuid) ||
                !Record->TryGetNumberField(TEXT("source_bones"), SourceBones) ||
                !Record->TryGetNumberField(TEXT("target_bones"), TargetBones) ||
                !Pair.SourcePath.StartsWith(TEXT("/Game/")) || !Pair.TargetPath.StartsWith(TEXT("/Game/")) ||
                Pair.SourcePath == Pair.TargetPath || !FMath::IsFinite(SourceBones) || !FMath::IsFinite(TargetBones) ||
                SourceBones < 1 || SourceBones > 65535 || TargetBones < 1 || TargetBones > 65535 ||
                SourceBones != static_cast<double>(static_cast<int32>(SourceBones)) ||
                TargetBones != static_cast<double>(static_cast<int32>(TargetBones)) ||
                OutPairs.ContainsByPredicate([&](const FRegisteredPair& Existing) { return SamePair(Existing, Pair.SourcePath, Pair.TargetPath); }))
            { OutDiagnostic = TEXT("Invalid or duplicate manifest pair; original manifest was preserved."); return false; }
            FGuid SourceGuid, TargetGuid;
            auto IsObjectPath = [](const FString& Path)
            {
                // Native validity plus project top-level path; no subobject/export-text aliases.
                return FPackageName::IsValidObjectPath(Path) && !Path.Contains(TEXT(":")) &&
                    Path.StartsWith(TEXT("/Game/"));
            };
            if (!FGuid::Parse(Pair.SourceGuid, SourceGuid) || !SourceGuid.IsValid() ||
                !FGuid::Parse(Pair.TargetGuid, TargetGuid) || !TargetGuid.IsValid() ||
                !IsObjectPath(Pair.SourcePath) || !IsObjectPath(Pair.TargetPath))
            { OutDiagnostic = TEXT("Invalid skeleton GUID or top-level object path; manifest preserved."); return false; }
            Pair.SourceBones = static_cast<int32>(SourceBones);
            Pair.TargetBones = static_cast<int32>(TargetBones);
            OutPairs.Add(MoveTemp(Pair));
        }
        return true;
    }

    bool WriteManifest(FString& OutDiagnostic)
    {
        auto Root = MakeShared<FJsonObject>();
        Root->SetNumberField(TEXT("schema_version"), 1);
        Root->SetStringField(TEXT("mapping_policy"), TEXT("kh3_same_name_local_pose"));
        Root->SetBoolField(TEXT("retail_runtime_adapter_installed"), false);
        TArray<TSharedPtr<FJsonValue>> Records;
        for (const FRegisteredPair& Pair : PairOwner->Pairs)
        {
            auto Record = MakeShared<FJsonObject>();
            Record->SetStringField(TEXT("source_skeleton"), Pair.SourcePath);
            Record->SetStringField(TEXT("target_skeleton"), Pair.TargetPath);
            Record->SetStringField(TEXT("source_guid"), Pair.SourceGuid);
            Record->SetStringField(TEXT("target_guid"), Pair.TargetGuid);
            Record->SetNumberField(TEXT("source_bones"), Pair.SourceBones);
            Record->SetNumberField(TEXT("target_bones"), Pair.TargetBones);
            Records.Add(MakeShared<FJsonValueObject>(Record));
        }
        Root->SetArrayField(TEXT("pairs"), Records);
        FString Text;
        if (!FJsonSerializer::Serialize(Root, TJsonWriterFactory<>::Create(&Text)))
        { OutDiagnostic = TEXT("Could not serialize compatibility manifest."); return false; }
        const FString Path = ManifestPath();
        IFileManager::Get().MakeDirectory(*FPaths::GetPath(Path), true);
        const FString Temp = Path + TEXT(".pending-") + FGuid::NewGuid().ToString(EGuidFormats::Digits);
        if (!FFileHelper::SaveStringToFile(Text, *Temp, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
        { OutDiagnostic = TEXT("Could not write compatibility manifest staging file."); return false; }
        FString Backup;
        TArray<uint8> PreviousBytes;
        if (IFileManager::Get().FileExists(*Path))
        {
            Backup = Path + TEXT(".backup-") + FGuid::NewGuid().ToString(EGuidFormats::Digits);
            TArray<uint8> BackupBytes;
            if (!FFileHelper::LoadFileToArray(PreviousBytes, *Path) ||
                IFileManager::Get().Copy(*Backup, *Path, false, false) != COPY_OK ||
                !FFileHelper::LoadFileToArray(BackupBytes, *Backup) || PreviousBytes != BackupBytes)
            { IFileManager::Get().Delete(*Temp); OutDiagnostic = TEXT("Could not preserve the previous compatibility manifest."); return false; }
        }
        if (!IFileManager::Get().Move(*Path, *Temp, true, false, false, true))
        {
            // This UE4 FileManager may remove the destination before MoveFile fails.
            TArray<uint8> Restored;
            const bool bRestored = Backup.IsEmpty() ||
                (IFileManager::Get().Copy(*Path, *Backup, true, false) == COPY_OK &&
                 FFileHelper::LoadFileToArray(Restored, *Path) && Restored == PreviousBytes);
            if (bRestored) { IFileManager::Get().Delete(*Temp); }
            OutDiagnostic = bRestored ? TEXT("Manifest replacement failed; previous manifest restored.") :
                FString::Printf(TEXT("Manifest replacement and restore failed; exact backup retained at %s and pending file at %s."), *Backup, *Temp);
            return false;
        }
        return true;
    }

    bool ReloadManifestInternal(FString& OutDiagnostic)
    {
        // Resolve and validate the entire replacement under separate GC roots before
        // touching a working registration. Missing/stale inputs preserve the session.
        auto CandidateOwner = MakeUnique<FRegisteredPairOwner>();
        if (!ReadManifest(CandidateOwner->Pairs, OutDiagnostic)) { return false; }
        for (FRegisteredPair& Pair : CandidateOwner->Pairs)
        {
            Pair.Source = LoadObject<USkeleton>(nullptr, *Pair.SourcePath);
            Pair.Target = LoadObject<USkeleton>(nullptr, *Pair.TargetPath);
            if (!IsValid(Pair.Source) || !IsValid(Pair.Target) ||
                Pair.Source->GetGuid().ToString() != Pair.SourceGuid || Pair.Target->GetGuid().ToString() != Pair.TargetGuid ||
                Pair.Source->GetReferenceSkeleton().GetNum() != Pair.SourceBones || Pair.Target->GetReferenceSkeleton().GetNum() != Pair.TargetBones)
            {
                OutDiagnostic = FString::Printf(TEXT("Saved pair identity changed or is unavailable: %s / %s; current registrations preserved."), *Pair.SourcePath, *Pair.TargetPath);
                return false;
            }
            if (!RebirthSkeletonCompatibility::ValidatePair(Pair.Source, Pair.Target, OutDiagnostic)) { return false; }
        }
        for (const FRegisteredPair& Pair : PairOwner->Pairs)
        { if (!FenceComponents(Pair.Source, Pair.Target, OutDiagnostic)) { return false; } }
        for (const FRegisteredPair& Pair : CandidateOwner->Pairs)
        { if (!FenceComponents(Pair.Source, Pair.Target, OutDiagnostic)) { return false; } }
        TArray<const FRegisteredPair*> Applied;
        for (const FRegisteredPair& Pair : CandidateOwner->Pairs)
        {
            if (!RebirthSkeletonCompatibility::RegisterPair(Pair.Source, Pair.Target, OutDiagnostic))
            {
                for (const FRegisteredPair* Added : Applied)
                { RebirthSkeletonCompatibility::UnregisterPair(Added->Source, Added->Target); }
                FString RollbackDiagnostic;
                bool bRestored = true;
                for (const FRegisteredPair& Previous : PairOwner->Pairs)
                {
                    if (!RebirthSkeletonCompatibility::RegisterPair(Previous.Source, Previous.Target, RollbackDiagnostic))
                    { bRestored = false; }
                }
                if (!bRestored) { OutDiagnostic += TEXT("; restoring an earlier registration also failed; assets remain preserved."); }
                return false;
            }
            Applied.Add(&Pair);
        }
        for (const FRegisteredPair& Previous : PairOwner->Pairs)
        {
            if (!CandidateOwner->Pairs.ContainsByPredicate([&](const FRegisteredPair& Pair)
                { return SamePair(Pair, Previous.SourcePath, Previous.TargetPath); }))
            { RebirthSkeletonCompatibility::UnregisterPair(Previous.Source, Previous.Target); }
        }
        PairOwner = MoveTemp(CandidateOwner);
        bManifestLoaded = true;
        OutDiagnostic = FString::Printf(TEXT("Loaded %d saved compatible skeleton pairs; original assets unchanged."), PairOwner->Pairs.Num());
        return true;
    }

    bool EnsureSavedPairsLoaded(bool bPersistManifest, FString& OutDiagnostic)
    {
        return !bPersistManifest || bManifestLoaded || ReloadManifestInternal(OutDiagnostic);
    }

    USkeleton* SkeletonFromAsset(const FAssetData& Data)
    {
        UObject* Object = Data.GetAsset(); // Only the two explicitly selected assets are loaded.
        if (USkeleton* Skeleton = Cast<USkeleton>(Object)) { return Skeleton; }
        if (USkeletalMesh* Mesh = Cast<USkeletalMesh>(Object)) { return Mesh->Skeleton; }
        return nullptr;
    }

    void AddSelectedPair(TArray<FAssetData> Selected)
    {
        if (Selected.Num() != 2) { return; }
        FString Diagnostic;
        TStrongObjectPtr<USkeleton> A(SkeletonFromAsset(Selected[0]));
        TStrongObjectPtr<USkeleton> B(SkeletonFromAsset(Selected[1]));
        const bool bSuccess = URebirthSkeletonCompatibilityEditorLibrary::RegisterCompatibleSkeletons(
            A.Get(), B.Get(), Diagnostic, true);
        if (bSuccess) { UE_LOG(LogRebirthSkeletonCompatibilityEditor, Display, TEXT("%s"), *Diagnostic); }
        else { UE_LOG(LogRebirthSkeletonCompatibilityEditor, Warning, TEXT("%s"), *Diagnostic); }
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(bSuccess ?
            TEXT("Skeleton compatibility saved. Skeleton compatibility saved. Open an animation and select its receiving mesh in the preview. In-game support still requires the runtime adapter.") : Diagnostic));
    }

    void ExtendSelectedMenu(FMenuBuilder& Menu, TArray<FAssetData> Selected)
    {
        Menu.AddMenuEntry(FText::FromString(TEXT("Add Selected SkelCompat")),
            FText::FromString(TEXT("Register these skeletons once and reuse their original animations without converting each clip.")),
            FSlateIcon(), FUIAction(FExecuteAction::CreateStatic(&AddSelectedPair, Selected)));
    }

    TSharedRef<FExtender> ExtendAssetMenu(const TArray<FAssetData>& Selected)
    {
        auto Extender = MakeShared<FExtender>();
        if (Selected.Num() == 2 && Selected.ContainsByPredicate([](const FAssetData& Asset)
            { return Asset.AssetClass != USkeleton::StaticClass()->GetFName() && Asset.AssetClass != USkeletalMesh::StaticClass()->GetFName(); }) == false)
        {
            Extender->AddMenuExtension(TEXT("GetAssetActions"), EExtensionHook::After, nullptr,
                FMenuExtensionDelegate::CreateStatic(&ExtendSelectedMenu, Selected));
        }
        return Extender;
    }

    void ReloadAfterEngineInit()
    {
        if (IsRunningCommandlet() || FParse::Param(FCommandLine::Get(), TEXT("RebirthCookedMaterialMetadataOnly"))) { return; }
        FString Diagnostic;
        if (!URebirthSkeletonCompatibilityEditorLibrary::ReloadCompatibilityManifest(Diagnostic))
        { UE_LOG(LogRebirthSkeletonCompatibilityEditor, Warning, TEXT("%s"), *Diagnostic); }
    }
}

bool URebirthSkeletonCompatibilityEditorLibrary::RegisterCompatibleSkeletons(USkeleton* A, USkeleton* B,
    FString& OutDiagnostic, bool bPersistManifest)
{
    FScopedMutation Mutation(OutDiagnostic);
    if (!Mutation.bAcquired || !IsValid(A) || !IsValid(B) || A == B) { return false; }
    TStrongObjectPtr<USkeleton> RootA(A), RootB(B);
    if (!EnsureSavedPairsLoaded(bPersistManifest, OutDiagnostic) || !FenceComponents(A, B, OutDiagnostic)) { return false; }
    if (!A->GetPathName().StartsWith(TEXT("/Game/")) || !B->GetPathName().StartsWith(TEXT("/Game/")))
    { OutDiagnostic = TEXT("Only project skeleton assets can be registered."); return false; }
    const TArray<FRegisteredPair> Previous = PairOwner->Pairs;
    int32 Index = PairOwner->Pairs.IndexOfByPredicate([&](const FRegisteredPair& Pair) { return SamePair(Pair, A->GetPathName(), B->GetPathName()); });
    const bool bWasActive = RebirthSkeletonCompatibility::AreCompatible(A, B);
    if (Index == INDEX_NONE)
    {
        if (PairOwner->Pairs.Num() >= MaxRegisteredPairs) { OutDiagnostic = TEXT("Compatibility pair limit reached."); return false; }
        Index = PairOwner->Pairs.AddDefaulted();
    }
    FRegisteredPair& Pair = PairOwner->Pairs[Index];
    Pair.Source = A; Pair.Target = B;
    Pair.SourcePath = A->GetPathName(); Pair.TargetPath = B->GetPathName();
    Pair.SourceGuid = A->GetGuid().ToString(); Pair.TargetGuid = B->GetGuid().ToString();
    Pair.SourceBones = A->GetReferenceSkeleton().GetNum(); Pair.TargetBones = B->GetReferenceSkeleton().GetNum();
    if (!RebirthSkeletonCompatibility::RegisterPair(A, B, OutDiagnostic)) { PairOwner->Pairs = Previous; return false; }
    if (bPersistManifest && !WriteManifest(OutDiagnostic))
    {
        if (!bWasActive) { RebirthSkeletonCompatibility::UnregisterPair(A, B); }
        PairOwner->Pairs = Previous;
        return false;
    }
    return true;
}

bool URebirthSkeletonCompatibilityEditorLibrary::UnregisterCompatibleSkeletons(USkeleton* A, USkeleton* B,
    FString& OutDiagnostic, bool bPersistManifest)
{
    FScopedMutation Mutation(OutDiagnostic);
    if (!Mutation.bAcquired || !IsValid(A) || !IsValid(B)) { return false; }
    TStrongObjectPtr<USkeleton> RootA(A), RootB(B);
    if (!EnsureSavedPairsLoaded(bPersistManifest, OutDiagnostic) || !FenceComponents(A, B, OutDiagnostic)) { return false; }
    const TArray<FRegisteredPair> Previous = PairOwner->Pairs;
    PairOwner->Pairs.RemoveAll([&](const FRegisteredPair& Pair) { return SamePair(Pair, A->GetPathName(), B->GetPathName()); });
    if (bPersistManifest && !WriteManifest(OutDiagnostic)) { PairOwner->Pairs = Previous; return false; }
    RebirthSkeletonCompatibility::UnregisterPair(A, B);
    OutDiagnostic = TEXT("Compatibility registration removed; original assets preserved.");
    return true;
}

bool URebirthSkeletonCompatibilityEditorLibrary::ReloadCompatibilityManifest(FString& OutDiagnostic)
{
    FScopedMutation Mutation(OutDiagnostic);
    return Mutation.bAcquired && ReloadManifestInternal(OutDiagnostic);
}

FString URebirthSkeletonCompatibilityEditorLibrary::GetCompatibilityDiagnostics()
{
    return RebirthSkeletonCompatibility::GetDiagnostics();
}

namespace RebirthSkeletonCompatibilityEditor
{
    void Startup()
    {
        FString Diagnostic;
        if (!MayEdit(Diagnostic)) { return; }
        FContentBrowserModule& ContentBrowser = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
        auto Delegate = FContentBrowserMenuExtender_SelectedAssets::CreateStatic(&ExtendAssetMenu);
        MenuExtenderHandle = Delegate.GetHandle();
        ContentBrowser.GetAllAssetViewContextMenuExtenders().Add(Delegate);
        if (GEngine) { ReloadAfterEngineInit(); }
        else { PostEngineInitHandle = FCoreDelegates::OnPostEngineInit.AddStatic(&ReloadAfterEngineInit); }
    }

    void Shutdown()
    {
        FCoreDelegates::OnPreExit.Remove(OwnerPreExitHandle);
        FCoreDelegates::OnPostEngineInit.Remove(PostEngineInitHandle);
        if (FModuleManager::Get().IsModuleLoaded(TEXT("ContentBrowser")))
        {
            auto& Extenders = FModuleManager::GetModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser")).GetAllAssetViewContextMenuExtenders();
            Extenders.RemoveAll([](const FContentBrowserMenuExtender_SelectedAssets& Delegate) { return Delegate.GetHandle() == MenuExtenderHandle; });
        }
        if (PairOwner.IsValid())
        {
            FString Diagnostic;
            FScopedMutation Mutation(Diagnostic);
            if (!Mutation.bAcquired)
            { UE_LOG(LogRebirthSkeletonCompatibilityEditor, Fatal, TEXT("Skeleton compatibility shutdown must precede UObject purge: %s"), *Diagnostic); }
            for (const FRegisteredPair& Pair : PairOwner->Pairs)
            {
                if (!FenceComponents(Pair.Source, Pair.Target, Diagnostic))
                { UE_LOG(LogRebirthSkeletonCompatibilityEditor, Fatal, TEXT("Cannot safely release compatible skeleton roots: %s"), *Diagnostic); }
            }
            for (const FRegisteredPair& Pair : PairOwner->Pairs)
            { RebirthSkeletonCompatibility::UnregisterPair(Pair.Source, Pair.Target); }
            PairOwner.Reset();
            bManifestLoaded = false;
        }
    }
}
