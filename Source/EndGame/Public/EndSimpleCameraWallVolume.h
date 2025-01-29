#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "ESimpleCameraCollisionProfileType.h"
#include "EndSimpleCameraWallVolume.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndSimpleCameraWallVolume : public AVolume {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ESimpleCameraCollisionProfileType CollisionProfileType;
    
public:
    AEndSimpleCameraWallVolume(const FObjectInitializer& ObjectInitializer);

};

