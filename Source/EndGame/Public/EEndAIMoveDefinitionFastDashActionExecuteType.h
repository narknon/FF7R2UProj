#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveDefinitionFastDashActionExecuteType.generated.h"

UENUM(BlueprintType)
enum class EEndAIMoveDefinitionFastDashActionExecuteType : uint8 {
    Always,
    Arrived,
    ArrivedNotify,
};

