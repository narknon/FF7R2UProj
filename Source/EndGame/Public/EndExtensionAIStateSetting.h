#pragma once
#include "CoreMinimal.h"
#include "EEndExtensionAIStateAnimation.h"
#include "EEndExtensionAIStateBattle.h"
#include "EEndExtensionAIStateBattleEvacuation.h"
#include "EEndExtensionAIStateConnectEncount.h"
#include "EEndExtensionAIStateDoNothing.h"
#include "EEndExtensionAIStateFieldAction.h"
#include "EEndExtensionAIStateFollow.h"
#include "EEndExtensionAIStateHintAnimal.h"
#include "EEndExtensionAIStateInterest.h"
#include "EEndExtensionAIStateLead.h"
#include "EEndExtensionAIStateMoveTo.h"
#include "EEndExtensionAIStateStay.h"
#include "EEndExtensionAIStateUnique.h"
#include "EEndExtensionAIStateWandering.h"
#include "EEndExtensionAIStateWildAnimal.h"
#include "EndExtensionAIStateSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndExtensionAIStateSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndExtensionAIStateDoNothing DoNothing;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndExtensionAIStateConnectEncount ConnectEncount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndExtensionAIStateBattle Battle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndExtensionAIStateStay Stay;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndExtensionAIStateMoveTo MoveTo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndExtensionAIStateLead Lead;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndExtensionAIStateFollow Follow;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndExtensionAIStateWandering Wandering;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndExtensionAIStateAnimation Animation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndExtensionAIStateUnique Unique;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndExtensionAIStateInterest Interest;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndExtensionAIStateWildAnimal WildAnimal;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndExtensionAIStateBattleEvacuation BattleEvacuation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndExtensionAIStateHintAnimal HintAnimal;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndExtensionAIStateFieldAction FieldAction;
    
    ENDGAME_API FEndExtensionAIStateSetting();
};

