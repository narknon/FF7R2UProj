#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ETargetResultMotionType.h"
#include "EndShootingGameResultSplineActor.generated.h"

class UEndShootingGameSplineComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndShootingGameResultSplineActor : public AActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndShootingGameSplineComponent* SplineComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CreateMeshName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ETargetResultMotionType MotionType;
    
public:
    AEndShootingGameResultSplineActor(const FObjectInitializer& ObjectInitializer);

};

