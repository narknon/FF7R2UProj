#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndActorBaseInterface.h"
#include "EndFieldMovementSettingInterface.h"
#include "EndFieldMovementSettingVolumeActor.generated.h"

class UEndFieldMovementSettingVolumeComponent;

UCLASS(Blueprintable)
class AEndFieldMovementSettingVolumeActor : public AActor, public IEndFieldMovementSettingInterface, public IEndActorBaseInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldMovementSettingVolumeComponent* SettingVolume;
    
public:
    AEndFieldMovementSettingVolumeActor(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

