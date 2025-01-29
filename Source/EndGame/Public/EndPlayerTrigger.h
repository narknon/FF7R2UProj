#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndPlayerTrigger.generated.h"

class UCapsuleComponent;

UCLASS(Blueprintable, NotPlaceable)
class ENDGAME_API AEndPlayerTrigger : public AActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UCapsuleComponent* CapsuleComponent;
    
public:
    AEndPlayerTrigger(const FObjectInitializer& ObjectInitializer);

};

