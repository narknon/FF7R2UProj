#include "RebirthPreviewMaterialResolver.h"

#include "RebirthMaterialPreviewSafety.h"
#include "Engine/Texture.h"
#include "MaterialShared.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/Material.h"
#include "Materials/MaterialExpressionTextureBase.h"
#include "Misc/PackageName.h"
#include "UObject/Package.h"

namespace RebirthPreviewMaterialResolver
{
    namespace
    {
        constexpr int32 MaxDepth = 64;
        constexpr int32 MaxParameters = 4096;
        TMap<FString, FCompanionRule> Rules;

        bool ValidateCompanionRegistration(const FCompanionRule& Rule, FString& OutError)
        {
            if (!IsInGameThread() || Rule.Fidelity.IsEmpty() ||
                !FPackageName::IsValidObjectPath(Rule.OriginalObjectPath) ||
                !FPackageName::IsValidObjectPath(Rule.PreviewObjectPath) ||
                !Rule.PreviewObjectPath.StartsWith(TEXT("/Game/RebirthCompatibility/EditorPreview/")) ||
                Rule.OriginalObjectPath == Rule.PreviewObjectPath)
            {
                OutError = TEXT("invalid_exact_companion_registration");
                return false;
            }
            return true;
        }

        bool Cooked(const UObject* Object)
        {
            const UPackage* Package = Object ? Object->GetOutermost() : nullptr;
            return Package && (Package->bIsCookedForEditor || Package->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly));
        }

        bool Pending(UMaterialInterface* Material, const RebirthMaterialPreviewSafety::FResult& Safety)
        {
            if (!Safety.bParentChainValid || Safety.bHasUnsupportedRenderState) { return false; }
            const FMaterialResource* Resource = Material->GetMaterialResource(GMaxRHIFeatureLevel);
            const FMaterialResource* Base = Material->GetMaterial()->GetMaterialResource(GMaxRHIFeatureLevel);
            return (Resource && !Resource->IsCompilationFinished()) || (Base && !Base->IsCompilationFinished()) ||
                Safety.Reason.StartsWith(TEXT("shader_resource_initialization_pending:"));
        }

        bool SameInfo(const FMaterialParameterInfo& A, const FMaterialParameterInfo& B)
        {
            return A.Name == B.Name && A.Association == B.Association && A.Index == B.Index;
        }

        bool HasInfo(const TArray<FMaterialParameterInfo>& Values, const FMaterialParameterInfo& Info)
        {
            return Values.ContainsByPredicate([&Info](const FMaterialParameterInfo& Value) { return SameInfo(Value, Info); });
        }

        bool AddUnique(TArray<FMaterialParameterInfo>& Values, const FMaterialParameterInfo& Info)
        {
            if (Info.Name.IsNone() || Values.Num() >= MaxParameters) { return false; }
            if (!HasInfo(Values, Info)) { Values.Add(Info); }
            return true;
        }
    }

    bool RegisterCompanion(const FCompanionRule& Rule, FString& OutError)
    {
        if (!ValidateCompanionRegistration(Rule, OutError)) { return false; }
        if (const FCompanionRule* Existing = Rules.Find(Rule.OriginalObjectPath))
        {
            if (Existing->PreviewObjectPath != Rule.PreviewObjectPath || Existing->Fidelity != Rule.Fidelity ||
                Existing->bAllowUniformOnlyChildren != Rule.bAllowUniformOnlyChildren)
            {
                OutError = TEXT("conflicting_companion_registration");
                return false;
            }
            return true;
        }
        if (Rules.Num() >= MaxParameters) { OutError = TEXT("companion_registration_count_limit"); return false; }
        Rules.Add(Rule.OriginalObjectPath, Rule);
        OutError.Reset();
        return true;
    }

    bool RegisterFallbackCompanion(const FCompanionRule& Rule, FString& OutError)
    {
        if (!ValidateCompanionRegistration(Rule, OutError)) { return false; }
        if (Rules.Contains(Rule.OriginalObjectPath))
        {
            OutError.Reset();
            return true;
        }
        return RegisterCompanion(Rule, OutError);
    }

    void ClearCompanions()
    {
        check(IsInGameThread());
        Rules.Reset();
    }

    FResult Resolve(UMaterialInterface* Original, UObject* TransientOwner)
    {
        FResult Result;
        if (!IsInGameThread() || !IsValid(Original))
        {
            Result.Reason = TEXT("material_resolution_requires_valid_source_on_game_thread");
            return Result;
        }
        const RebirthMaterialPreviewSafety::FResult OriginalSafety = RebirthMaterialPreviewSafety::Evaluate(Original);
        if (OriginalSafety.bCanRender)
        {
            Result.Material = Original;
            Result.bUsesOriginalResource = true;
            Result.Fidelity = TEXT("Original material shader resources");
            return Result;
        }
        if (!OriginalSafety.bParentChainValid)
        {
            Result.Reason = OriginalSafety.Reason;
            return Result;
        }
        Result.bPendingShaderResources = Pending(Original, OriginalSafety);

        TArray<UMaterialInstance*> Children;
        UMaterialInterface* Current = Original;
        const FCompanionRule* Match = nullptr;
        for (int32 Depth = 0; Current && Depth < MaxDepth; ++Depth)
        {
            Match = Rules.Find(Current->GetPathName());
            if (Match) { break; }
            UMaterialInstance* Child = Cast<UMaterialInstance>(Current);
            if (!Child) { break; }
            // A cooked descendant may contain baked static features not represented
            // by the companion. Never infer shader equivalence from its parent name.
            if (Cooked(Child) || !Child->GetStaticParameters().IsEmpty() || Child->HasOverridenBaseProperties() ||
                Child->FontParameterValues.Num() || Child->RuntimeVirtualTextureParameterValues.Num() ||
                Child->ShaderResourceBufferParameterValues.Num())
            {
                Result.Reason = TEXT("no_exact_companion_for_cooked_static_or_nonuniform_variant:") + Child->GetPathName();
                return Result;
            }
            Children.Add(Child);
            Current = Child->Parent;
        }
        if (!Match || (Children.Num() && !Match->bAllowUniformOnlyChildren))
        {
            Result.Reason = TEXT("no_registered_preview_companion:") + Original->GetPathName();
            return Result;
        }

        UMaterialInterface* Companion = LoadObject<UMaterialInterface>(nullptr, *Match->PreviewObjectPath);
        const RebirthMaterialPreviewSafety::FResult Safety = RebirthMaterialPreviewSafety::Evaluate(Companion);
        if (!Safety.bCanRender)
        {
            Result.bPendingShaderResources = Result.bPendingShaderResources || (Companion && Pending(Companion, Safety));
            Result.Reason = TEXT("preview_companion_not_ready:") + Safety.Reason;
            return Result;
        }
        Result.Fidelity = Match->Fidelity;
        // Result.bPendingShaderResources still says whether the original itself is compiling (the recovered in-game
        // shading of a cooked chain): callers keep retrying and switch to the original once it can render.
        if (!Children.Num()) { Result.Material = Companion; return Result; }

        TArray<FMaterialParameterInfo> Scalars, Vectors, Textures;
        for (UMaterialInstance* Child : Children)
        {
            if (Child->ScalarParameterValues.Num() > MaxParameters || Child->VectorParameterValues.Num() > MaxParameters ||
                Child->TextureParameterValues.Num() > MaxParameters)
            {
                Result.Reason = TEXT("uniform_child_parameter_count_limit"); return Result;
            }
            for (const FScalarParameterValue& Value : Child->ScalarParameterValues)
                if (!AddUnique(Scalars, Value.ParameterInfo)) { Result.Reason = TEXT("invalid_scalar_override_info"); return Result; }
            for (const FVectorParameterValue& Value : Child->VectorParameterValues)
                if (!AddUnique(Vectors, Value.ParameterInfo)) { Result.Reason = TEXT("invalid_vector_override_info"); return Result; }
            for (const FTextureParameterValue& Value : Child->TextureParameterValues)
                if (!AddUnique(Textures, Value.ParameterInfo)) { Result.Reason = TEXT("invalid_texture_override_info"); return Result; }
        }

        TArray<FMaterialParameterInfo> NativeScalars, NativeVectors, NativeTextures;
        TArray<FGuid> Guids;
        Companion->GetAllScalarParameterInfo(NativeScalars, Guids);
        Companion->GetAllVectorParameterInfo(NativeVectors, Guids);
        Companion->GetAllTextureParameterInfo(NativeTextures, Guids);
        for (const FMaterialParameterInfo& Info : Scalars)
            if (!HasInfo(NativeScalars, Info)) { Result.Reason = TEXT("scalar_override_not_represented_by_preview:") + Info.Name.ToString(); return Result; }
        for (const FMaterialParameterInfo& Info : Vectors)
            if (!HasInfo(NativeVectors, Info)) { Result.Reason = TEXT("vector_override_not_represented_by_preview:") + Info.Name.ToString(); return Result; }
        for (const FMaterialParameterInfo& Info : Textures)
            if (!HasInfo(NativeTextures, Info)) { Result.Reason = TEXT("texture_override_not_represented_by_preview:") + Info.Name.ToString(); return Result; }

        UMaterialInstanceDynamic* Dynamic = UMaterialInstanceDynamic::Create(Companion, TransientOwner ? TransientOwner : GetTransientPackage());
        if (!Dynamic) { Result.Reason = TEXT("could_not_create_transient_preview_instance"); return Result; }
        Dynamic->SetFlags(RF_Transient);
        for (const FMaterialParameterInfo& Info : Scalars)
        {
            float Value = 0.0f;
            if (!Original->GetScalarParameterValue(FHashedMaterialParameterInfo(Info), Value) || !FMath::IsFinite(Value))
            { Result.Reason = TEXT("invalid_effective_scalar:") + Info.Name.ToString(); return Result; }
            Dynamic->SetScalarParameterValueByInfo(Info, Value);
        }
        for (const FMaterialParameterInfo& Info : Vectors)
        {
            FLinearColor Value;
            if (!Original->GetVectorParameterValue(FHashedMaterialParameterInfo(Info), Value) ||
                !FMath::IsFinite(Value.R) || !FMath::IsFinite(Value.G) || !FMath::IsFinite(Value.B) || !FMath::IsFinite(Value.A))
            { Result.Reason = TEXT("invalid_effective_vector:") + Info.Name.ToString(); return Result; }
            Dynamic->SetVectorParameterValueByInfo(Info, Value);
        }
        for (const FMaterialParameterInfo& Info : Textures)
        {
            UTexture* Value = nullptr;
            UTexture* NativeValue = nullptr;
            if (!Original->GetTextureParameterValue(FHashedMaterialParameterInfo(Info), Value) || (Value && !IsValid(Value)))
            { Result.Reason = TEXT("invalid_effective_texture:") + Info.Name.ToString(); return Result; }
            if (!Companion->GetTextureParameterValue(FHashedMaterialParameterInfo(Info), NativeValue) ||
                (NativeValue && !IsValid(NativeValue)) || ((Value == nullptr) != (NativeValue == nullptr)) ||
                (Value && (Value->GetMaterialType() != NativeValue->GetMaterialType() ||
                    UMaterialExpressionTextureBase::GetSamplerTypeForTexture(Value) != UMaterialExpressionTextureBase::GetSamplerTypeForTexture(NativeValue))))
            { Result.Reason = TEXT("texture_override_dimension_or_sampler_not_represented_by_preview:") + Info.Name.ToString(); return Result; }
            Dynamic->SetTextureParameterValueByInfo(Info, Value);
        }
        const RebirthMaterialPreviewSafety::FResult DynamicSafety = RebirthMaterialPreviewSafety::Evaluate(Dynamic);
        if (!DynamicSafety.bCanRender)
        {
            Result.bPendingShaderResources = Result.bPendingShaderResources || Pending(Dynamic, DynamicSafety);
            Result.Reason = TEXT("transient_preview_instance_not_ready:") + DynamicSafety.Reason;
            return Result;
        }
        Result.Material = Dynamic;
        return Result;
    }
}
