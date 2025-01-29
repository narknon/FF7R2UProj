#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndBikeSpline.generated.h"

class UEndBikeSplineComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndBikeSpline : public AActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBikeSplineComponent* mSplineComponent;
    
public:
    AEndBikeSpline(const FObjectInitializer& ObjectInitializer);

};

