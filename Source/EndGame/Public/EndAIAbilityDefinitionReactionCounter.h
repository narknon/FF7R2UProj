#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAbilityCommandType.h"
#include "EndAIAbilityDefinition.h"
#include "EndAIReactionInfoAbility.h"
#include "EndAIReactionInfoCommand.h"
#include "EndAIReactionInfoDamageSource.h"
#include "EndAIReactionInfoDamageSource_Property.h"
#include "EndAIReactionInfoOther.h"
#include "EndAIAbilityDefinitionReactionCounter.generated.h"

UCLASS(Blueprintable)
class UEndAIAbilityDefinitionReactionCounter : public UEndAIAbilityDefinition {
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
    TArray<FEndAIReactionInfoDamageSource> ReactionInfoDamageSources;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIReactionInfoDamageSource_Property> ReactionInfoDamageSources_Property;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIReactionInfoOther> ReactionInfoOther;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCanExecDamage;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> IgnoreDamageSources;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> FatMoogleIgnoreAbilitys_UCPC;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bOverrideActionAfterInterval;
    
    UEndAIAbilityDefinitionReactionCounter();

};

