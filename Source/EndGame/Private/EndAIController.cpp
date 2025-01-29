#include "EndAIController.h"
#include "EndAIActionComponent.h"
#include "EndAIMoveComponent.h"

AEndAIController::AEndAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bSetControlRotationFromPawnOrientation = false;
    this->m_BehaviorTreeAsset = NULL;
    this->m_DefaultAIStateID = EEndAIState::EMPTY;
    this->m_StartInFlyMode = false;
    this->m_TickForceOnGameThread = false;
    this->m_bUseFieldNavNotOnBattleNav = false;
    this->AIMoveComponent = CreateDefaultSubobject<UEndAIMoveComponent>(TEXT("EndAIMoveComponent"));
    this->AIActionComponent = CreateDefaultSubobject<UEndAIActionComponent>(TEXT("EndAIActionComponent"));
}


