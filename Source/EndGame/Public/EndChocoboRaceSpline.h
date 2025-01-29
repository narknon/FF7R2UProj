#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndChocoboRaceSpline.generated.h"

class AEndChocoboRaceSpline;
class UEndChocoboRaceSplineComponent;

UCLASS(Blueprintable)
class AEndChocoboRaceSpline : public AActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndChocoboRaceSplineComponent* SplineComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AEndChocoboRaceSpline* NextMainCourseSpline;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AEndChocoboRaceSpline* NextSubCourseSpline;
    
public:
    AEndChocoboRaceSpline(const FObjectInitializer& ObjectInitializer);

};

