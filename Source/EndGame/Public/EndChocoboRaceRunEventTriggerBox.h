#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboRaceRunEventType.h"
#include "EndTriggerBox.h"
#include "EndChocoboRaceRunEventTriggerBox.generated.h"

UCLASS(Blueprintable)
class AEndChocoboRaceRunEventTriggerBox : public AEndTriggerBox {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndChocoboRaceRunEventType EventType;
    
public:
    AEndChocoboRaceRunEventTriggerBox(const FObjectInitializer& ObjectInitializer);

};

