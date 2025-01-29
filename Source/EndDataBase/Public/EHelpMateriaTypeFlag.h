#pragma once
#include "CoreMinimal.h"
#include "EHelpMateriaTypeFlag.generated.h"

UENUM()
enum class EHelpMateriaTypeFlag {
    EHelpMateriaTypeFlag_Attribute = 1,
    EHelpMateriaTypeFlag_AddEffect,
    EHelpMateriaTypeFlag_Trigger = 4,
    EHelpMateriaTypeFlag_APup = 8,
    EHelpMateriaTypeFlag_MPSave = 16,
    EHelpMateriaTypeFlag_Range = 32,
    EHelpMateriaTypeFlag_HPAbsorb = 64,
    EHelpMateriaTypeFlag_MPAbsorb = 128,
    EHelpMateriaTypeFlag_AutoMagic = 256,
    EHelpMateriaTypeFlag_MateriaLevelUP = 512,
    EHelpMateriaTypeFlag_MagicPowerUp = 1024,
    EHelpMateriaTypeFlag_QuickCast = 2048,
    EHelpMateriaTypeFlag_Max = 12 UMETA(Hidden),
};

