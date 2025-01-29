#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndCinemaCameraManagerSettingActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndCinemaCameraManagerSettingActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, meta=(AllowPrivateAccess=true))
    float LightClippingDistance;
    
    AEndCinemaCameraManagerSettingActor(const FObjectInitializer& ObjectInitializer);

protected:
    UFUNCTION(BlueprintCallable)
    void SetLightClippingDistance(float InValue);
    
};

