#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EEndVehicleSEVelocityDetectionTypes.h"
#include "EndVehicleSeSetting.h"
#include "EndVehicleSEComponent.generated.h"

class USkeletalMeshComponent;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndVehicleSEComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bStartOnPlay: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EEndVehicleSEVelocityDetectionTypes::Type> VelocityDetectionType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndVehicleSeSetting SeSetting;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    USkeletalMeshComponent* MeshComponent;
    
public:
    UEndVehicleSEComponent(const FObjectInitializer& ObjectInitializer);

};

