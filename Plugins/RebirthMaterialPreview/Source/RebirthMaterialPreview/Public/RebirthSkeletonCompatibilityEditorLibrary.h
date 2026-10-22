#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RebirthSkeletonCompatibilityEditorLibrary.generated.h"

class USkeleton;

UCLASS()
class REBIRTHMATERIALPREVIEW_API URebirthSkeletonCompatibilityEditorLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Rebirth|Skeleton Compatibility")
    static bool RegisterCompatibleSkeletons(USkeleton* A, USkeleton* B, FString& OutDiagnostic, bool bPersistManifest = true);

    UFUNCTION(BlueprintCallable, Category="Rebirth|Skeleton Compatibility")
    static bool UnregisterCompatibleSkeletons(USkeleton* A, USkeleton* B, FString& OutDiagnostic, bool bPersistManifest = true);

    UFUNCTION(BlueprintCallable, Category="Rebirth|Skeleton Compatibility")
    static bool ReloadCompatibilityManifest(FString& OutDiagnostic);

    UFUNCTION(BlueprintPure, Category="Rebirth|Skeleton Compatibility")
    static FString GetCompatibilityDiagnostics();
};

namespace RebirthSkeletonCompatibilityEditor
{
    void Startup();
    void Shutdown();
}
