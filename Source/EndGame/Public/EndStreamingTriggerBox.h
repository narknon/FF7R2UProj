#pragma once
#include "CoreMinimal.h"
#include "EndStreamingTrigger.h"
#include "EndStreamingTriggerBox.generated.h"

UCLASS(Abstract, Blueprintable)
class AEndStreamingTriggerBox : public AEndStreamingTrigger {
    GENERATED_BODY()
public:
    AEndStreamingTriggerBox(const FObjectInitializer& ObjectInitializer);

};

