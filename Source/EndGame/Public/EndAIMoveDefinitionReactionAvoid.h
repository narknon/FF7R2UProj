#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAbilityCommandType.h"
#include "EndAIMoveDefinition.h"
#include "Templates/SubclassOf.h"
#include "EndAIMoveDefinitionReactionAvoid.generated.h"

class UEndAIMoveDefinitionStep;

UCLASS(Blueprintable)
class UEndAIMoveDefinitionReactionAvoid : public UEndAIMoveDefinition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndBattleAbilityCommandType> CommandTypes;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<TSubclassOf<UEndAIMoveDefinitionStep>> StepMoveDefinitionClassList_Front;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<TSubclassOf<UEndAIMoveDefinitionStep>> StepMoveDefinitionClassList_Right;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<TSubclassOf<UEndAIMoveDefinitionStep>> StepMoveDefinitionClassList_Left;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<TSubclassOf<UEndAIMoveDefinitionStep>> StepMoveDefinitionClassList_Special;
    
    UEndAIMoveDefinitionReactionAvoid();

};

