#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndDolphinJumpSplineActor.generated.h"

class UEndDolphinJumpSplineComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndDolphinJumpSplineActor : public AActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndDolphinJumpSplineComponent* SplineComponent;
    
public:
    AEndDolphinJumpSplineActor(const FObjectInitializer& ObjectInitializer);

};

