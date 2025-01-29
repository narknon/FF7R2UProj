#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndAerialIgnoreVolume.generated.h"

class UEndAerialIgnoreComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndAerialIgnoreVolume : public AActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndAerialIgnoreComponent* AerialIgnoreComponent;
    
public:
    AEndAerialIgnoreVolume(const FObjectInitializer& ObjectInitializer);

};

