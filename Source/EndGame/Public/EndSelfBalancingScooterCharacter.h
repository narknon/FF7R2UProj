#pragma once
#include "CoreMinimal.h"
#include "EScooterColor.h"
#include "EndPlayerCharacter.h"
#include "EndVehicleSeSetting.h"
#include "EndSelfBalancingScooterCharacter.generated.h"

class AEndCharacterBase;
class UEndSBScooterMovementSetting;

UCLASS(Blueprintable)
class ENDGAME_API AEndSelfBalancingScooterCharacter : public AEndPlayerCharacter {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndSBScooterMovementSetting* MovementSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EScooterColor ScooterColor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndVehicleSeSetting SeSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndCharacterBase* RiderActor;
    
public:
    AEndSelfBalancingScooterCharacter(const FObjectInitializer& ObjectInitializer);

};

