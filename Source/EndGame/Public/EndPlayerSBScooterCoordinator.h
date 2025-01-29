#pragma once
#include "CoreMinimal.h"
#include "EndPlayerVehicleCoordinatorBase.h"
#include "EndPlayerSBScooterCoordinator.generated.h"

class AActor;
class AEndCharacterBase;
class UEndUserWidget;

UCLASS(Blueprintable)
class ENDGAME_API UEndPlayerSBScooterCoordinator : public UEndPlayerVehicleCoordinatorBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndCharacterBase* VehicleChara;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndCharacterBase* RiderChara;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Export, Transient, meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<UEndUserWidget> m_TopUI;
    
public:
    UEndPlayerSBScooterCoordinator();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    AActor* GetVehicleCharacter() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    AEndCharacterBase* GetRiderCharacter(int32 Index) const;
    
};

