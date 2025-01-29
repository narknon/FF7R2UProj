#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionStateManagedActor.h"
#include "EndFieldActionTinyBroncoPortActor.generated.h"

class UFXSystemAsset;
class USphereComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndFieldActionTinyBroncoPortActor : public AEndFieldActionStateManagedActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USphereComponent* OverlapVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UFXSystemAsset* PortEffect;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float InteractionRadius;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float IconInputSuccessTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TriggerName;
    
public:
    AEndFieldActionTinyBroncoPortActor(const FObjectInitializer& ObjectInitializer);

};

