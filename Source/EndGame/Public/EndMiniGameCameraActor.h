#pragma once
#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "EndMiniGameCameraActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndMiniGameCameraActor : public ACameraActor {
    GENERATED_BODY()
public:
    AEndMiniGameCameraActor(const FObjectInitializer& ObjectInitializer);

};

