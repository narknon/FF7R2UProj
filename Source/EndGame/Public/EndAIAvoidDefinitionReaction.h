#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAbilityCommandType.h"
#include "EndAIActionDefinitionBase.h"
#include "EndAIReactionInfoAbility.h"
#include "EndAIReactionInfoCommand.h"
#include "EndAIReactionInfoOther.h"
#include "Templates/SubclassOf.h"
#include "EndAIAvoidDefinitionReaction.generated.h"

class UEndAIAnimDefinitionAvoid;

UCLASS(Blueprintable)
class UEndAIAvoidDefinitionReaction : public UEndAIActionDefinitionBase {
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
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<TSubclassOf<UEndAIAnimDefinitionAvoid>> AnimDefinitionAvoidClassList_Front;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<TSubclassOf<UEndAIAnimDefinitionAvoid>> AnimDefinitionAvoidClassList_Right;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<TSubclassOf<UEndAIAnimDefinitionAvoid>> AnimDefinitionAvoidClassList_Left;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<TSubclassOf<UEndAIAnimDefinitionAvoid>> AnimDefinitionAvoidClassList_Special;
    
    UEndAIAvoidDefinitionReaction();

};

