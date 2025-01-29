#pragma once
#include "CoreMinimal.h"
#include "EDataObjectType.generated.h"

UENUM(BlueprintType)
enum class EDataObjectType : uint8 {
    EDataObjectType_RESIDNET,
    EDataObjectType_DEBUG,
    EDataObjectType_FILED_LIST,
};

