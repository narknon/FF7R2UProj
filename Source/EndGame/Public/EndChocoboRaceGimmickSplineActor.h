#pragma once
#include "CoreMinimal.h"
#include "EndChocoboRaceGimmickSplineActorBase.h"
#include "EndChocoboRaceGimmickSplineActor.generated.h"

class AActor;
class AEndChocoboRaceBombBalloonActor;
class AEndDynamicBodyCollisionActor;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndChocoboRaceGimmickSplineActor : public AEndChocoboRaceGimmickSplineActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AActor* TargetActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<AEndChocoboRaceBombBalloonActor> BombActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndDynamicBodyCollisionActor* PushCollisionActor;
    
public:
    AEndChocoboRaceGimmickSplineActor(const FObjectInitializer& ObjectInitializer);

};

