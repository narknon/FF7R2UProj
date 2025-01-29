#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EBattleAbilityRotateNotifyState.h"
#include "EndBattleAbilityRotateState.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class UEndBattleAbilityRotateState : public UAnimNotifyState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EBattleAbilityRotateNotifyState::Type> Type;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float GoalAngle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FrameDeltaTimeSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bKeepRotateAfterInterrupted;
    
    UEndBattleAbilityRotateState();

};

