#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndNotGenerateAerialPointsVolume.generated.h"

class UBoxComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndNotGenerateAerialPointsVolume : public AActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> territoryID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UBoxComponent* BoxComponent;
    
public:
    AEndNotGenerateAerialPointsVolume(const FObjectInitializer& ObjectInitializer);

};

