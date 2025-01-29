#pragma once
#include "CoreMinimal.h"
#include "ESQEXSEADAutoSePartsType.generated.h"

UENUM(BlueprintType)
namespace ESQEXSEADAutoSePartsType {
    enum Type {
        Invalid,
        Foot,
        Arm,
        Wing,
        Swing,
        Body,
    };
}

