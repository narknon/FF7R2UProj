#pragma once
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "EndFieldMovingWalkwaySplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldMovingWalkwaySplineComponent : public USplineComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AutoMovingSpeed;
    
    UEndFieldMovingWalkwaySplineComponent(const FObjectInitializer& ObjectInitializer);

};

