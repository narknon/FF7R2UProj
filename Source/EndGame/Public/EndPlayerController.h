#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EndAIModelControllerInterface.h"
#include "Templates/SubclassOf.h"
#include "EndPlayerController.generated.h"

class AEndBattleTalkOnEndBattleActor;
class AEndCharacter;
class AEndPlayerTrigger;
class UEndPlayerExistNavAreaComponent;
class UEndPlayerLeaderActionParamComponent;
class UEndPlayerVehicleCoordinatorBase;

UCLASS(Blueprintable, Config=Engine)
class ENDGAME_API AEndPlayerController : public APlayerController, public IEndAIModelControllerInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndPlayerExistNavAreaComponent* PlayerExistNavAreaComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndPlayerLeaderActionParamComponent* PlayerLeaderActionParamComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AEndCharacter* LeaderCharacter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndBattleTalkOnEndBattleActor> BattleTalkOnEndBattleClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AEndBattleTalkOnEndBattleActor* BattleTalkOnEndBattle;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UEndPlayerVehicleCoordinatorBase* ActiveVehicleCoordinator;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TMap<uint8, UEndPlayerVehicleCoordinatorBase*> VehicleCoordinators;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndPlayerTrigger* PlayerTrigger;
    
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaxMouseSensitivity;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MinMouseSensitivity;
    
    AEndPlayerController(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

