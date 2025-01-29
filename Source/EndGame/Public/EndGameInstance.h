#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EndGameInstance.generated.h"

UCLASS(Blueprintable, NonTransient)
class ENDGAME_API UEndGameInstance : public UGameInstance {
    GENERATED_BODY()
public:
    UEndGameInstance();

};

