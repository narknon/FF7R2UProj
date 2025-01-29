#pragma once
#include "CoreMinimal.h"
#include "EndFieldSwitchAccessAnimUnit.h"
#include "EndFieldSwitchAccessSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldSwitchAccessSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldSwitchAccessAnimUnit> AnimationUnits;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FirstStartAnimationTimeRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLastAnimIsLoop;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLastAnimIsKeep;
    
    ENDGAME_API FEndFieldSwitchAccessSetting();
};

