#pragma once
#include "CoreMinimal.h"
#include "StreamLevelPackageExist.generated.h"

UENUM(BlueprintType)
enum class StreamLevelPackageExist : uint8 {
    StreamLevelPackageExist_RESET,
    StreamLevelPackageExist_NONE_FILE,
    StreamLevelPackageExist_EXIT_FILE,
};

