#pragma once
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "EndAIEnemyFieldSetting.generated.h"

class UEndAIFieldDefinitionBase;

USTRUCT(BlueprintType)
struct FEndAIEnemyFieldSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIFieldDefinitionBase> FieldDefinition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 ApplyMax;
    
    ENDGAME_API FEndAIEnemyFieldSetting();
};

