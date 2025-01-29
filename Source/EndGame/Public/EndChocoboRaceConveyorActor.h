#pragma once
#include "CoreMinimal.h"
#include "EndChocoboRaceConveyorActorBase.h"
#include "Templates/SubclassOf.h"
#include "EndChocoboRaceConveyorActor.generated.h"

class AEndEnvironmentSkeletalMeshActor;

UCLASS(Blueprintable)
class AEndChocoboRaceConveyorActor : public AEndChocoboRaceConveyorActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Speed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndEnvironmentSkeletalMeshActor> ConveyorClass;
    
public:
    AEndChocoboRaceConveyorActor(const FObjectInitializer& ObjectInitializer);

};

