#pragma once
#include "CoreMinimal.h"
#include "ESQEXSEADAudioVolumeCommand.generated.h"

UENUM(BlueprintType)
namespace ESQEXSEADAudioVolumeCommand {
    enum Type {
        None,
        Set,
        Reset,
    };
}

