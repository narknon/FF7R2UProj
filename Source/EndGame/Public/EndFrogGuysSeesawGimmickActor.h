#pragma once
#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "EndFrogGuysGimmickActor.h"
#include "EndFrogGuysSeesawGimmickActor.generated.h"

class AActor;
class UPrimitiveComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndFrogGuysSeesawGimmickActor : public AEndFrogGuysGimmickActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaximumExtraAngleDiff;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ReturnAngularSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AngularSpeedPerDistance;
    
public:
    AEndFrogGuysSeesawGimmickActor(const FObjectInitializer& ObjectInitializer);

protected:
    UFUNCTION(BlueprintCallable)
    void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
};

