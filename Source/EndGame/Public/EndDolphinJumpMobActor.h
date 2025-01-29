#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndDolphinJumpMobActor.generated.h"

class USplineComponent;

UCLASS(Blueprintable)
class AEndDolphinJumpMobActor : public AActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USplineComponent* SplineComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StartOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SpeedScale;
    
public:
    AEndDolphinJumpMobActor(const FObjectInitializer& ObjectInitializer);

};

