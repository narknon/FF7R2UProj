#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionDamageReciveVolumeBase.h"
#include "EndSimpleShootingTargetVolume.generated.h"

class UEndFieldActionShootingTargetComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndSimpleShootingTargetVolume : public AEndFieldActionDamageReciveVolumeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionShootingTargetComponent* ShootingTargetComponent;
    
    AEndSimpleShootingTargetVolume(const FObjectInitializer& ObjectInitializer);

};

