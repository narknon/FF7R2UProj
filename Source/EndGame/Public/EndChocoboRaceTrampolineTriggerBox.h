#pragma once
#include "CoreMinimal.h"
#include "EndTriggerBox.h"
#include "EndChocoboRaceTrampolineTriggerBox.generated.h"

class AEndTargetPoint;

UCLASS(Blueprintable)
class AEndChocoboRaceTrampolineTriggerBox : public AEndTriggerBox {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<AEndTargetPoint> JumpTargetPoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName JumpTargetPointName;
    
public:
    AEndChocoboRaceTrampolineTriggerBox(const FObjectInitializer& ObjectInitializer);

};

