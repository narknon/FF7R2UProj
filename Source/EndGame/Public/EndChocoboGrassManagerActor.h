#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndChocoboGrassManagerActor.generated.h"

class AEndChocoboGrassPoint;

UCLASS(Blueprintable)
class AEndChocoboGrassManagerActor : public AActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TArray<AEndChocoboGrassPoint*> GrassPointUpdateList;
    
public:
    AEndChocoboGrassManagerActor(const FObjectInitializer& ObjectInitializer);

};

