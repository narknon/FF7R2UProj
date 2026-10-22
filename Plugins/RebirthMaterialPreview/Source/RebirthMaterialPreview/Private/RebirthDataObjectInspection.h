#pragma once

#include "CoreMinimal.h"

class FJsonObject;
class UObject;

// Read-only snapshot of an already loaded EndDataObject. Does not load assets,
// execute gameplay, save packages, or alter the row map. Requires EndDataObject
// and JsonUtilities module dependencies in the integrating module.
void AppendEndDataObjectDiagnostics(
    UObject* Asset,
    const TSharedRef<FJsonObject>& Diagnostics,
    int32 MaxRows = 100);
