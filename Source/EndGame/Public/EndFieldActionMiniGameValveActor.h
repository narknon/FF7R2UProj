#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionValveActor.h"
#include "EndFieldActionMiniGameValveActor.generated.h"

UCLASS(Abstract, Blueprintable)
class AEndFieldActionMiniGameValveActor : public AEndFieldActionValveActor {
    GENERATED_BODY()
public:
    AEndFieldActionMiniGameValveActor(const FObjectInitializer& ObjectInitializer);

};

