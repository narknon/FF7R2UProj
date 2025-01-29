#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndChocoboJetOneWayGuideActor.generated.h"

class UEndChocoboJetOneWayGuideSplineComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndChocoboJetOneWayGuideActor : public AActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TimeOut;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndChocoboJetOneWayGuideSplineComponent* SplineComponent;
    
public:
    AEndChocoboJetOneWayGuideActor(const FObjectInitializer& ObjectInitializer);

};

