#pragma once
#include "CoreMinimal.h"
#include "EClimbingJumpPointType.h"
#include "EndFieldJumpPointSettingBase.h"
#include "EndFieldClimbingJumpPointSetting.generated.h"

class AEndFieldActionClimbingActor;
class AEndFieldActionHookRopeActor;

USTRUCT(BlueprintType)
struct FEndFieldClimbingJumpPointSetting : public FEndFieldJumpPointSettingBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EClimbingJumpPointType JumpPointType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AEndFieldActionHookRopeActor* HookRopeActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AEndFieldActionClimbingActor* ClimbingActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 ClimbingPointIndex;
    
    ENDGAME_API FEndFieldClimbingJumpPointSetting();
};

