#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EndEnvQueryContext_CurrentTargetTransform.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndEnvQueryContext_CurrentTargetTransform : public UEnvQueryContext {
    GENERATED_BODY()
public:
    UEndEnvQueryContext_CurrentTargetTransform();

};

