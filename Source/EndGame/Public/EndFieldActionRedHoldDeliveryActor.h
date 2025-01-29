#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionSaveActorBase.h"
#include "EndFieldRedHoldDeliverySetting.h"
#include "Templates/SubclassOf.h"
#include "EndFieldActionRedHoldDeliveryActor.generated.h"

class AEndRedHoldDeliveryStaticMeshActor;
class UEndFieldActionTriggerComponent;

UCLASS(Abstract, Blueprintable)
class AEndFieldActionRedHoldDeliveryActor : public AEndFieldActionSaveActorBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* RedHoldDeliveryVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldRedHoldDeliverySetting> HoldObjects;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndRedHoldDeliveryStaticMeshActor> DeliveryObjectClass;
    
    AEndFieldActionRedHoldDeliveryActor(const FObjectInitializer& ObjectInitializer);

};

