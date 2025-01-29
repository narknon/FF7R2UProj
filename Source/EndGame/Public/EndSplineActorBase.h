#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndSplineActorBase.generated.h"

class USplineComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndSplineActorBase : public AActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USplineComponent* SplineMoveComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool IsLoop;
    
public:
    AEndSplineActorBase(const FObjectInitializer& ObjectInitializer);

};

