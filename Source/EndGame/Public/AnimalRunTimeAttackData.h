#pragma once
#include "CoreMinimal.h"
#include "AnimalRunTimeAttackData.generated.h"

USTRUCT(BlueprintType)
struct FAnimalRunTimeAttackData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 BestTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TriggerName;
    
    ENDGAME_API FAnimalRunTimeAttackData();
};

