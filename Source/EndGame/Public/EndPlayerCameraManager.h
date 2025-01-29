#pragma once
#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "EndPlayerCameraManager.generated.h"

class ACameraActor;
class UEndCompositeCollisionComponent;
class UEndGrassCollisionComponent;

UCLASS(Blueprintable, NonTransient)
class ENDGAME_API AEndPlayerCameraManager : public APlayerCameraManager {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndGrassCollisionComponent* GrassCollisionComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndCompositeCollisionComponent* CompositeCollisionComponent;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ACameraActor* MainCameraActor;
    
public:
    AEndPlayerCameraManager(const FObjectInitializer& ObjectInitializer);

};

