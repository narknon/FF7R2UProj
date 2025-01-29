#pragma once
#include "CoreMinimal.h"
#include "EndTreasurePointParameters.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndTreasurePointParameters {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TreasureID;
    
    FEndTreasurePointParameters();
};

