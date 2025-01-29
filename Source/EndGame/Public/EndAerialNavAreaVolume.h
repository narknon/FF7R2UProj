#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndAerialInterface.h"
#include "EndAerialModule.h"
#include "EndAerialNavAreaVolume.generated.h"

class UEndAerialNavBoxComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndAerialNavAreaVolume : public AActor, public IEndAerialInterface {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAerialModule AerialModule;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndAerialNavBoxComponent* EndArealNavBox;
    
public:
    AEndAerialNavAreaVolume(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

