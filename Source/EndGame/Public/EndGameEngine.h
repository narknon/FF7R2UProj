#pragma once
#include "CoreMinimal.h"
#include "Engine/GameEngine.h"
#include "EndGameEngine.generated.h"

UCLASS(Blueprintable, MinimalAPI, NonTransient, NotPlaceable)
class UEndGameEngine : public UGameEngine {
    GENERATED_BODY()
public:
    UEndGameEngine();

};

