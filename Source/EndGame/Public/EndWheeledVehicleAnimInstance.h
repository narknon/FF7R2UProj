#pragma once
#include "CoreMinimal.h"
#include "EndSkeletalMeshActorAnimInstance.h"
#include "EndVehicleRangedCurveParam.h"
#include "EndWheelAnimSetup.h"
#include "EndWheeledVehicleAnimInstance.generated.h"

class AEndWheeledVehicle;
class UWheeledVehicleMovementComponent;

UCLASS(Blueprintable, NonTransient)
class ENDGAME_API UEndWheeledVehicleAnimInstance : public UEndSkeletalMeshActorAnimInstance {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndVehicleRangedCurveParam SteerAngleRateCurve;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndWheelAnimSetup> WheelSetups;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SuspensionMaxRaise;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SuspensionMaxDrop;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UWheeledVehicleMovementComponent* WheeledVehicleMovementComponent;
    
public:
    UEndWheeledVehicleAnimInstance();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    AEndWheeledVehicle* GetVehicle() const;
    
};

