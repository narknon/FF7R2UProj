#pragma once
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "EndWaterFlowSplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndWaterFlowSplineComponent : public USplineComponent {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> FlowSpeeds;
    
public:
    UEndWaterFlowSplineComponent(const FObjectInitializer& ObjectInitializer);

};

