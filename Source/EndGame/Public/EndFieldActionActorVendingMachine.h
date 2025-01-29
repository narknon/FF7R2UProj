#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionStateManagedActor.h"
#include "EndInteractorInterface.h"
#include "EndFieldActionActorVendingMachine.generated.h"

class UEndFieldActionTriggerComponent;
class UEndNavModifierComponent;

UCLASS(Abstract, Blueprintable)
class AEndFieldActionActorVendingMachine : public AEndFieldActionStateManagedActor, public IEndInteractorInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ShopActionID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MenuTextID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* PressVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNavModifierComponent* ModifierVolume;
    
    AEndFieldActionActorVendingMachine(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

