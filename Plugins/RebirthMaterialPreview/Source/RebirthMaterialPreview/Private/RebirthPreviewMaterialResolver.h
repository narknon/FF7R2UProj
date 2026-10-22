#pragma once

#include "CoreMinimal.h"

class UMaterialInterface;

namespace RebirthPreviewMaterialResolver
{
    struct FCompanionRule
    {
        FString OriginalObjectPath;
        FString PreviewObjectPath;
        FString Fidelity;
        bool bAllowUniformOnlyChildren = true;
    };

    struct FResult
    {
        // The caller must GC-own this reference (component material or UPROPERTY)
        // before retaining it. Resolve is game-thread-only and never saves assets.
        UMaterialInterface* Material = nullptr;
        FString Reason;
        FString Fidelity;
        bool bUsesOriginalResource = false;
        bool bPendingShaderResources = false;
    };

    // Exact provenance registrations, independent of character or asset names.
    bool RegisterCompanion(const FCompanionRule& Rule, FString& OutError);
    // Validated embedded defaults never replace an already registered exact rule.
    bool RegisterFallbackCompanion(const FCompanionRule& Rule, FString& OutError);
    void ClearCompanions();
    FResult Resolve(UMaterialInterface* Original, UObject* TransientOwner);
}
