#pragma once
#include "CoreMinimal.h"
#include "EndPlayerVehicleCoordinatorBase.h"
#include "EndPlayerTinyBroncoCoordinator.generated.h"

class AActor;
class AEndCharacterBase;

UCLASS(Blueprintable)
class ENDGAME_API UEndPlayerTinyBroncoCoordinator : public UEndPlayerVehicleCoordinatorBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndCharacterBase* VehicleChara;
    
public:
    UEndPlayerTinyBroncoCoordinator();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    AActor* GetVehicleCharacter() const;
    
};

