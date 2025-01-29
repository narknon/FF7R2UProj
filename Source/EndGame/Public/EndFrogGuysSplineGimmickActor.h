#pragma once
#include "CoreMinimal.h"
#include "EEndFrogGuysSplineMoveState.h"
#include "EndFrogGuysGimmickActor.h"
#include "EndFrogGuysSplineGimmickActor.generated.h"

class USceneComponent;
class USplineComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndFrogGuysSplineGimmickActor : public AEndFrogGuysGimmickActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USplineComponent* SplineComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USceneComponent* SplineMoveComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SplineMoveSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SplineStopTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndFrogGuysSplineMoveState SplineMoveStartState;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SplineMoveStartTime;
    
public:
    AEndFrogGuysSplineGimmickActor(const FObjectInitializer& ObjectInitializer);

};

