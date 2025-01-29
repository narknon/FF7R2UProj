#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndAnimalRunSafeWarpBox.generated.h"

class UBoxComponent;

UCLASS(Blueprintable)
class AEndAnimalRunSafeWarpBox : public AActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UBoxComponent* BoxComponent;
    
public:
    AEndAnimalRunSafeWarpBox(const FObjectInitializer& ObjectInitializer);

};

