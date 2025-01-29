#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAbilityCommandType.h"
#include "EndAIGuardDefinition.h"
#include "EndAIReactionInfoAbility.h"
#include "EndAIReactionInfoCommand.h"
#include "EndAIReactionInfoOther.h"
#include "EndAIGuardDefinitionReaction.generated.h"

UCLASS(Blueprintable)
class UEndAIGuardDefinitionReaction : public UEndAIGuardDefinition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndBattleAbilityCommandType> CommandTypes;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIReactionInfoCommand> ReactionInfoCommands;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ReactionAbilityIds;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIReactionInfoAbility> ReactionInfoAbilitys;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIReactionInfoOther> ReactionInfoOther;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> FatMoogleIgnoreAbilitys_UCPC;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bOverrideActionAfterInterval;
    
    UEndAIGuardDefinitionReaction();

};

