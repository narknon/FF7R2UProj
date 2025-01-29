#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionSaveActorBase.h"
#include "EndFieldVaultActionLineActor.generated.h"

class UEndFieldActionTriggerComponent;
class UEndFieldVaultActionLineComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndFieldVaultActionLineActor : public AEndFieldActionSaveActorBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldVaultActionLineComponent* SplineMoveComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* UpperVolume;
    
public:
    AEndFieldVaultActionLineActor(const FObjectInitializer& ObjectInitializer);

};

