#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndFieldActionWallVolume.generated.h"

class UBoxComponent;

UCLASS(Blueprintable)
class AEndFieldActionWallVolume : public AActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UBoxComponent* BoxComponent;
    
public:
    AEndFieldActionWallVolume(const FObjectInitializer& ObjectInitializer);

};

