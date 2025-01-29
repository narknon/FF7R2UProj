#pragma once
#include "CoreMinimal.h"
#include "EndChocoboRaceGimmickActorBase.h"
#include "Templates/SubclassOf.h"
#include "EndChocoboRaceIronBallActor.generated.h"

class AEndEnvironmentSkeletalMeshActor;

UCLASS(Blueprintable)
class AEndChocoboRaceIronBallActor : public AEndChocoboRaceGimmickActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndEnvironmentSkeletalMeshActor> IronBallClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AngularVelocity;
    
public:
    AEndChocoboRaceIronBallActor(const FObjectInitializer& ObjectInitializer);

};

