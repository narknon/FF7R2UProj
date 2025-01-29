#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChocoboRaceGimmickSplineWaitPoint.h"
#include "EndChocoboRaceGimmickSplineActorBase.generated.h"

class USplineComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndChocoboRaceGimmickSplineActorBase : public AActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USplineComponent* GimmickSplineComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MoveSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FChocoboRaceGimmickSplineWaitPoint> WaitPoints;
    
public:
    AEndChocoboRaceGimmickSplineActorBase(const FObjectInitializer& ObjectInitializer);

};

