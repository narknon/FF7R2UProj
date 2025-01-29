#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndNavGridLayerDivisionVolume.generated.h"

class UBoxComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndNavGridLayerDivisionVolume : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UBoxComponent* BoxComponent;
    
    AEndNavGridLayerDivisionVolume(const FObjectInitializer& ObjectInitializer);

};

