#pragma once
#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "EndRigCameraActor.generated.h"

UCLASS(Blueprintable)
class AEndRigCameraActor : public ACameraActor {
    GENERATED_BODY()
public:
    AEndRigCameraActor(const FObjectInitializer& ObjectInitializer);

};

