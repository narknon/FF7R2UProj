#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Templates/SubclassOf.h"
#include "EndAIBattlePlayerAutoMagicInfo.generated.h"

class UEndAIBattlePlayerAutoMagicRule;

UCLASS(Blueprintable)
class UEndAIBattlePlayerAutoMagicInfo : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, TSubclassOf<UEndAIBattlePlayerAutoMagicRule>> EvaluationRules;
    
    UEndAIBattlePlayerAutoMagicInfo();

};

