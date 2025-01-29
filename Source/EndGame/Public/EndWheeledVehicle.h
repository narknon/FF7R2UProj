#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "EndPhysicsSeSetting.h"
#include "EndSkeletalMeshActorBase.h"
#include "EndVehicleSeSetting.h"
#include "Templates/SubclassOf.h"
#include "EndWheeledVehicle.generated.h"

class AActor;
class AEndWheeledVehiclePlayerController;
class UActorComponent;
class UEndPhysicalMaterial;
class UEndWheeledVehicleActionParams;
class UEndWheeledVehicleMovementComponent;
class UPrimitiveComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndWheeledVehicle : public AEndSkeletalMeshActorBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndWheeledVehicleMovementComponent* VehicleMovement;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TMap<FName, UActorComponent*> ComponentTable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndWheeledVehiclePlayerController> PlayerControllerClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndWheeledVehicleActionParams* ActionParams;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndPhysicalMaterial* InteriorPhysicalMaterial;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AActor* VehicleController;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndVehicleSeSetting SeSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndPhysicsSeSetting PhysSeSetting;
    
public:
    AEndWheeledVehicle(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
};

