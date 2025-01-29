#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionActorBenchBreak.h"
#include "EndFieldActionActorCampBreak.generated.h"

class UEndFieldActionTriggerComponent;

UCLASS(Blueprintable)
class AEndFieldActionActorCampBreak : public AEndFieldActionActorBenchBreak {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CampStartMenuActionName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CheckCompletedHubId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CampStartTriggerName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* TickableVolume;
    
    AEndFieldActionActorCampBreak(const FObjectInitializer& ObjectInitializer);

};

