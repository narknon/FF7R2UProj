#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionSaveActorBase.h"
#include "EndFieldActionSpiderMoveActor.generated.h"

class UEndFieldActionTriggerComponent;

UCLASS(Abstract, Blueprintable)
class AEndFieldActionSpiderMoveActor : public AEndFieldActionSaveActorBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* TickableVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FrontWallDistance;
    
    AEndFieldActionSpiderMoveActor(const FObjectInitializer& ObjectInitializer);

};

