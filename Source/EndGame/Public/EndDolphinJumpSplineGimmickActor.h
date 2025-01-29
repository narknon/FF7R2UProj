#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndDolphinJumpSplineGimmickActor.generated.h"

class USceneComponent;
class USplineComponent;

UCLASS(Blueprintable)
class AEndDolphinJumpSplineGimmickActor : public AActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USplineComponent* SplineComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USceneComponent* SplineMoveComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StopSeconds;
    
public:
    AEndDolphinJumpSplineGimmickActor(const FObjectInitializer& ObjectInitializer);

};

