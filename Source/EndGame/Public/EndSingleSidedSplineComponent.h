#pragma once
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "EndSingleSidedSplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndSingleSidedSplineComponent : public USplineComponent {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bValidRightSide;
    
public:
    UEndSingleSidedSplineComponent(const FObjectInitializer& ObjectInitializer);

};

