#pragma once
#include "CoreMinimal.h"
#include "EVfxMaterialParameter_MeshFlags.generated.h"

UENUM()
enum class EVfxMaterialParameter_MeshFlags {
    None,
    Mesh_00,
    Mesh_01,
    Mesh_02 = 4,
    Mesh_03 = 8,
    Mesh_04 = 16,
    Mesh_05 = 32,
    Mesh_06 = 64,
    Mesh_07 = 128,
    Mesh_08 = 256,
    Mesh_09 = 512,
    Mesh_10 = 1024,
    Mesh_All = -1,
};

