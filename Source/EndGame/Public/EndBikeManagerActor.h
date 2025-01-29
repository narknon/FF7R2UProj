#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndBikeManagerActor.generated.h"

class AEndBikePlayerControllerBase;
class UObject;

UCLASS(Blueprintable)
class AEndBikeManagerActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndBikePlayerControllerBase* pPlayerController;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TSet<UObject*> ReferenceObjects;
    
    AEndBikeManagerActor(const FObjectInitializer& ObjectInitializer);

};

