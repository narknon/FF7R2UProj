#pragma once
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "EndFieldMovementControlSplineComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldMovementControlSplineComponent : public USplineComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bSnapPosition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bSnapRotation;
    
    UEndFieldMovementControlSplineComponent(const FObjectInitializer& ObjectInitializer);

};

