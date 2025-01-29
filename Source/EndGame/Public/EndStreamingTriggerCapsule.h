#pragma once
#include "CoreMinimal.h"
#include "EndStreamingTrigger.h"
#include "EndStreamingTriggerCapsule.generated.h"

UCLASS(Abstract, Blueprintable)
class AEndStreamingTriggerCapsule : public AEndStreamingTrigger {
    GENERATED_BODY()
public:
    AEndStreamingTriggerCapsule(const FObjectInitializer& ObjectInitializer);

};

