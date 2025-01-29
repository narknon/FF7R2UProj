#pragma once
#include "CoreMinimal.h"
#include "EEndMenuReportIconKind.generated.h"

UENUM(BlueprintType)
enum class EEndMenuReportIconKind : uint8 {
    CommunicationTower,
    SubjugationPoint,
    LifeSpot,
    StoryPoint,
    ChocoboFootTrace,
    ChocoboFeedingGround,
    SummonMonsterSmallShrine,
    CraftRecipeExcavatePoint,
    SecretSubjugationPoint,
};

