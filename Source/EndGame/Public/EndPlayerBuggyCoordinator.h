#pragma once
#include "CoreMinimal.h"
#include "EndPlayerVehicleCoordinatorBase.h"
#include "EndPlayerBuggyCoordinator.generated.h"

class AActor;
class AEndCharacterBase;
class AEndWheeledVehicleSplineMoveBattleEscape;

UCLASS(Blueprintable)
class ENDGAME_API UEndPlayerBuggyCoordinator : public UEndPlayerVehicleCoordinatorBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AActor* VehicleChara;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndCharacterBase* MainRiderChara;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndWheeledVehicleSplineMoveBattleEscape* BattleEscapeSplineActor;
    
public:
    UEndPlayerBuggyCoordinator();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    AActor* GetVehicleCharacter() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    AEndCharacterBase* GetRiderCharacter(int32 Index) const;
    
};

