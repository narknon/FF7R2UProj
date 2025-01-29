#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndWallInterface.h"
#include "EndWallModule.h"
#include "EndWallNavAreaVolume.generated.h"

class UEndWallNavBoxComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndWallNavAreaVolume : public AActor, public IEndWallInterface {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndWallModule WallModule;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndWallNavBoxComponent* EndWallNavBox;
    
public:
    AEndWallNavAreaVolume(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

