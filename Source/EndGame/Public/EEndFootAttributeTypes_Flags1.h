#pragma once
#include "CoreMinimal.h"
#include "EEndFootAttributeTypes_Flags1.generated.h"

UENUM()
enum class EEndFootAttributeTypes_Flags1 {
    None,
    Metal_Parts = 2,
    Metal_Floor = 4,
    Metal_Ami = 8,
    Con_Clean = 16,
    Con_Sandmix = 32,
    Con_Water = 64,
    Wood_Floor = 128,
    Wood_Parts = 256,
    Wood_Old = 512,
    Soil = 1024,
    Stone = 2048,
    Gravel = 4096,
    Grass = 8192,
    Carpet = 16384,
    Glass = 32768,
    Sand = 65536,
    Crap_Con = 131072,
    Crap_Pla = 262144,
    Crap_Tra = 524288,
    Woodchip = 1048576,
    Water_Default = 2097152,
    Water_Swamp = 4194304,
    Rubber = 8388608,
    Metal_Totan = 16777216,
    Metal_Cavity = 33554432,
    Metal_Frame = 67108864,
    Wood_Piller = 134217728,
    Tarp = 268435456,
    Slimy = 536870912,
    Water_River = 1073741824,
    Water_Ocean = -1,
};

