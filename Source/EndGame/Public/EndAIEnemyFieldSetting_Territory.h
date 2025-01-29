#pragma once
#include "CoreMinimal.h"
#include "EndAIEnemyFieldSetting.h"
#include "EndAIEnemyFieldSetting_Territory.generated.h"

USTRUCT(BlueprintType)
struct FEndAIEnemyFieldSetting_Territory {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName FieldAIName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIEnemyFieldSetting> DefinitionSettings;
    
    ENDGAME_API FEndAIEnemyFieldSetting_Territory();
};

