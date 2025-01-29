#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EEndCharacterControllerStateType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsCharaState.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsCharaState : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector m_Source;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndCharacterControllerStateType> m_CharaStates;
    
    UEndBTDecorator_IsCharaState();

};

