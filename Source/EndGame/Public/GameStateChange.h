#pragma once
#include "CoreMinimal.h"
#include "EGameState.h"
#include "GameStateChange.generated.h"

USTRUCT(BlueprintType)
struct FGameStateChange {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EGameState State;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool ChangeIn;
    
    ENDGAME_API FGameStateChange();
};

