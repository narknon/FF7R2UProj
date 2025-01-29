#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldJumpPointSettingBase.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldJumpPointSettingBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform TargetTransform;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableJumpPoint;
    
    ENDGAME_API FEndFieldJumpPointSettingBase();
};

