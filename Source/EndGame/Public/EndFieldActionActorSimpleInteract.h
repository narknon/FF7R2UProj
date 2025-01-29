#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionStateManagedActor.h"
#include "EndFieldSimpleInteractNameMatching.h"
#include "EndFieldSimpleInteractTransformMatching.h"
#include "EndFieldActionActorSimpleInteract.generated.h"

class UEndFieldActionTriggerComponent;
class UEndFieldSimpleInteractStateActionBase;

UCLASS(Blueprintable)
class AEndFieldActionActorSimpleInteract : public AEndFieldActionStateManagedActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* TikableAreaVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldSimpleInteractStateActionBase* StateAction;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, EditFixedSize, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldSimpleInteractNameMatching> MatchingNameArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, EditFixedSize, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldSimpleInteractTransformMatching> MachingTransformArray;
    
    AEndFieldActionActorSimpleInteract(const FObjectInitializer& ObjectInitializer);

};

