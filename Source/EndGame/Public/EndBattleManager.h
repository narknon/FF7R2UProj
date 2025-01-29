#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EndBattleManager.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndBattleManager : public UGameInstanceSubsystem {
    GENERATED_BODY()
public:
    UEndBattleManager();

};

