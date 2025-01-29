#pragma once
#include "CoreMinimal.h"
#include "EndChocoboRaceConveyorActorBase.h"
#include "Templates/SubclassOf.h"
#include "EndChocoboRaceCircleConveyorActor.generated.h"

class AEndEnvironmentSkeletalMeshActor;

UCLASS(Blueprintable)
class AEndChocoboRaceCircleConveyorActor : public AEndChocoboRaceConveyorActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AngularVelocity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndEnvironmentSkeletalMeshActor> CircleClass;
    
public:
    AEndChocoboRaceCircleConveyorActor(const FObjectInitializer& ObjectInitializer);

};

