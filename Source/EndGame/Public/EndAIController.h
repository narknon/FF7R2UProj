#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "EEndAIState.h"
#include "EndAIModelControllerInterface.h"
#include "EndAIParam.h"
#include "EndExtensionAIStateSetting.h"
#include "EndAIController.generated.h"

class UBehaviorTree;
class UEndAIActionComponent;
class UEndAIMoveComponent;

UCLASS(Blueprintable, MinimalAPI)
class AEndAIController : public AAIController, public IEndAIModelControllerInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBehaviorTree* m_BehaviorTreeAsset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIState m_DefaultAIStateID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndExtensionAIStateSetting m_DefaultExAIStateSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAIParam m_AIParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_StartInFlyMode;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_TickForceOnGameThread;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_bUseFieldNavNotOnBattleNav;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndAIMoveComponent* AIMoveComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndAIActionComponent* AIActionComponent;
    
public:
    AEndAIController(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

