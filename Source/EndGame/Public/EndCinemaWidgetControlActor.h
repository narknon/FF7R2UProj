#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndCinemaWidgetControlActor.generated.h"

class UEndCinemaWidgetControlComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndCinemaWidgetControlActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCinemaWidgetControlComponent* ControllerComponent;
    
    AEndCinemaWidgetControlActor(const FObjectInitializer& ObjectInitializer);

};

