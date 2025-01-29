#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndCinemaMaterialAnimateTimeActor.generated.h"

class UEndCinemaMaterialAnimateTimeComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndCinemaMaterialAnimateTimeActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCinemaMaterialAnimateTimeComponent* ControllerComponent;
    
    AEndCinemaMaterialAnimateTimeActor(const FObjectInitializer& ObjectInitializer);

};

