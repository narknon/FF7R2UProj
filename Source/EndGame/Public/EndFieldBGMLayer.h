#pragma once
#include "CoreMinimal.h"
#include "EndFieldBGMLayer.generated.h"

UENUM(BlueprintType)
enum class EndFieldBGMLayer : uint8 {
    EndFieldBGMLayer_Debug,
    EndFieldBGMLayer_CutScene,
    EndFieldBGMLayer_PlannerEvent,
    EndFieldBGMLayer_MiniGame,
    EndFieldBGMLayer_Quest,
    EndFieldBGMLayer_Battle,
    EndFieldBGMLayer_PreBattle,
    EndFieldBGMLayer_Vehicle,
    EndFieldBGMLayer_LevelFieldLower,
    EndFieldBGMLayer_WorldField,
    EndFieldBGMLayer_Title,
};

