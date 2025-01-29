#pragma once
#include "CoreMinimal.h"
#include "EndShootingGameTargetActorBase.h"
#include "EndShootingGameTargetSplineActor.generated.h"

class UEndShootingGameSplineComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndShootingGameTargetSplineActor : public AEndShootingGameTargetActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndShootingGameSplineComponent* SplineComponent;
    
public:
    AEndShootingGameTargetSplineActor(const FObjectInitializer& ObjectInitializer);

};

