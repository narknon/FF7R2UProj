#pragma once
#include "CoreMinimal.h"
#include "EndEnvQueryContext_BlackboardTarget.h"
#include "EndEnvQueryContext_TeleportBaseTarget.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndEnvQueryContext_TeleportBaseTarget : public UEndEnvQueryContext_BlackboardTarget {
    GENERATED_BODY()
public:
    UEndEnvQueryContext_TeleportBaseTarget();

};

