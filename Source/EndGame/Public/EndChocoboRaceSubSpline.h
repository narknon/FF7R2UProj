#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndChocoboRaceSubSpline.generated.h"

class UEndChocoboRaceSplineComponent;

UCLASS(Blueprintable)
class AEndChocoboRaceSubSpline : public AActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndChocoboRaceSplineComponent* SplineComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Probability;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Capacity;
    
public:
    AEndChocoboRaceSubSpline(const FObjectInitializer& ObjectInitializer);

};

