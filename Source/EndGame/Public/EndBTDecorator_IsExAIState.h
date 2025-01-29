#pragma once
#include "CoreMinimal.h"
#include "EEndExtensionAIStateAnimation.h"
#include "EEndExtensionAIStateBattle.h"
#include "EEndExtensionAIStateBattleEvacuation.h"
#include "EEndExtensionAIStateConnectEncount.h"
#include "EEndExtensionAIStateFollow.h"
#include "EEndExtensionAIStateInterest.h"
#include "EEndExtensionAIStateLead.h"
#include "EEndExtensionAIStateMoveTo.h"
#include "EEndExtensionAIStateStay.h"
#include "EEndExtensionAIStateUnique.h"
#include "EEndExtensionAIStateWandering.h"
#include "EEndExtensionAIStateWildAnimal.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsExAIState.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsExAIState : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndExtensionAIStateConnectEncount> ExAIStates_ConnectEncount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndExtensionAIStateBattle> ExAIStates_Battle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndExtensionAIStateStay> ExAIStates_Stay;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndExtensionAIStateMoveTo> ExAIStates_MoveTo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndExtensionAIStateLead> ExAIStates_Lead;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndExtensionAIStateFollow> ExAIStates_Follow;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndExtensionAIStateWandering> ExAIStates_Wandering;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndExtensionAIStateAnimation> ExAIStates_Animation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndExtensionAIStateUnique> ExAIStates_Unique;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndExtensionAIStateInterest> ExAIStates_Interest;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndExtensionAIStateWildAnimal> ExAIStates_WildAnimal;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndExtensionAIStateBattleEvacuation> ExAIStates_BattleEvacuation;
    
    UEndBTDecorator_IsExAIState();

};

