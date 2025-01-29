#pragma once
#include "CoreMinimal.h"
#include "EndLocomotionAnimGroupSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndLocomotionAnimGroupSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> Animations;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> PoseMatchingTimings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool bOverride;
    
    ENDGAME_API FEndLocomotionAnimGroupSetting();
};

