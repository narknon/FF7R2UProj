#pragma once
#include "CoreMinimal.h"
#include "EndMiniGameCameraActor.h"
#include "EndCraneMiniGameCameraActor.generated.h"

class USplineComponent;

UCLASS(Blueprintable)
class AEndCraneMiniGameCameraActor : public AEndMiniGameCameraActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USplineComponent* SplineComponent;
    
public:
    AEndCraneMiniGameCameraActor(const FObjectInitializer& ObjectInitializer);

};

