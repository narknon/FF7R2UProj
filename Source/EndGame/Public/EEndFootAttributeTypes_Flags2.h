#pragma once
#include "CoreMinimal.h"
#include "EEndFootAttributeTypes_Flags2.generated.h"

UENUM(BlueprintType)
enum class EEndFootAttributeTypes_Flags2 : uint8 {
    None,
    Water_SandSwamp,
    Water_Default_Shallow,
    Water_Swamp_Shallow = 4,
    Water_River_Shallow = 8,
    Water_Ocean_Shallow = 16,
    Water_SandSwamp_Shallow = 32,
};

