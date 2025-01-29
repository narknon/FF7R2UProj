#pragma once
#include "CoreMinimal.h"
#include "EndPlayerVehicleCoordinatorBase.h"
#include "EndPlayerChocoboCoordinator.generated.h"

class AActor;
class AEndCharacter;
class AEndCharacterBase;

UCLASS(Blueprintable)
class ENDGAME_API UEndPlayerChocoboCoordinator : public UEndPlayerVehicleCoordinatorBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndCharacter* VehicleChara;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndCharacter* RiderChara;
    
public:
    UEndPlayerChocoboCoordinator();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    AActor* GetVehicleCharacter() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    AEndCharacterBase* GetRiderCharacter(int32 Index) const;
    
};

