#pragma once
#include "CoreMinimal.h"
#include "EEndAIReactionPlayerType.h"
#include "EEndBattleDamageSourceProperty.h"
#include "EndAIReactionInfoDamageSource_Property.generated.h"

USTRUCT(BlueprintType)
struct FEndAIReactionInfoDamageSource_Property {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBattleDamageSourceProperty DamageSource_Property;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIReactionPlayerType PlayerType;
    
    ENDGAME_API FEndAIReactionInfoDamageSource_Property();
};

