#pragma once

#include "CoreMinimal.h"

class UMaterialInterface;

namespace RebirthMaterialFamilySnapshot
{
    // Pure inspection of already-loaded objects. No material mutation,
    // compilation, asset loading or saving. Root may expose this FString from
    // an existing diagnostics UFUNCTION for the owned Python generator.
    FString Inspect(UMaterialInterface* Material);
}
