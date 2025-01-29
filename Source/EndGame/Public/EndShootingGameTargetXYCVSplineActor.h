#pragma once
#include "CoreMinimal.h"
#include "EndShootingGameTargetActorBase.h"
#include "EndShootingGameTargetXYCVSplineActor.generated.h"

class UEndShootingGameSplineComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndShootingGameTargetXYCVSplineActor : public AEndShootingGameTargetActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndShootingGameSplineComponent* SplineComponent;
    
public:
    AEndShootingGameTargetXYCVSplineActor(const FObjectInitializer& ObjectInitializer);

};

