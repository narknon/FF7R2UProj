#pragma once
#include "CoreMinimal.h"
#include "EndAIComboDefinition.h"
#include "EndAIReactionInfoAbility.h"
#include "EndAIReactionInfoCommand.h"
#include "EndAIReactionInfoOther.h"
#include "EndAIComboDefinitionReactionCounter.generated.h"

UCLASS(Blueprintable)
class UEndAIComboDefinitionReactionCounter : public UEndAIComboDefinition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIReactionInfoCommand> ReactionInfoCommands;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIReactionInfoAbility> ReactionInfoAbilitys;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIReactionInfoOther> ReactionInfoOther;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCanExecDamage;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> IgnoreDamageSources;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> FatMoogleIgnoreAbilitys_UCPC;
    
    UEndAIComboDefinitionReactionCounter();

};

