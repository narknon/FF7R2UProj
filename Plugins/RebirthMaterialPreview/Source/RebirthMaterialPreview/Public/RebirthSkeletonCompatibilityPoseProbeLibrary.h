#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RebirthSkeletonCompatibilityPoseProbeLibrary.generated.h"
class UAnimSequence;
class USkeleton;
class USkeletalMesh;

// Owned private-host diagnostic. It does not register, convert, bake or save assets.
UCLASS()
class REBIRTHMATERIALPREVIEW_API URebirthSkeletonCompatibilityPoseProbeLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Rebirth|Skeleton Compatibility|Diagnostics")
    static bool AreSkeletonsCompatible(USkeleton* A, USkeleton* B);

    UFUNCTION(BlueprintCallable, Category="Rebirth|Skeleton Compatibility|Diagnostics")
    static FString InspectRegisteredPair(USkeleton* A, USkeleton* B);

    UFUNCTION(BlueprintCallable, Category="Rebirth|Skeleton Compatibility|Diagnostics")
    static FString ValidateOriginalCompressedPose(UAnimSequence* SourceAnimation, USkeleton* ReceivingSkeleton,
        USkeletalMesh* ReceivingMesh = nullptr, int32 SampleCount = 17, bool bExpectRegistered = true);
};
