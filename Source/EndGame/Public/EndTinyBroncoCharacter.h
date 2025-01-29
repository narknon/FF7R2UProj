#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "EndPlayerCharacter.h"
#include "EndVehicleSeSetting.h"
#include "EndTinyBroncoCharacter.generated.h"

class AActor;
class UEndTinyBroncoMovementSetting;
class UPrimitiveComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndTinyBroncoCharacter : public AEndPlayerCharacter {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndTinyBroncoMovementSetting* MovementSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndVehicleSeSetting SeSetting;
    
public:
    AEndTinyBroncoCharacter(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
};

