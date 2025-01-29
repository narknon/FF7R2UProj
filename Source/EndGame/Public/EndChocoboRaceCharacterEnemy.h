#pragma once
#include "CoreMinimal.h"
#include "EndChocoboRaceCharacterBase.h"
#include "EndChocoboRaceCharacterEnemy.generated.h"

USTRUCT(BlueprintType)
struct FEndChocoboRaceCharacterEnemy : public FEndChocoboRaceCharacterBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndChocoboRaceCharacterEnemy();
};

