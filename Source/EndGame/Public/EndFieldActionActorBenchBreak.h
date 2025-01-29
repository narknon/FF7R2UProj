#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionStateManagedActor.h"
#include "Templates/SubclassOf.h"
#include "EndFieldActionActorBenchBreak.generated.h"

class AEndSkeletalMeshActor;
class UEndFieldActionTriggerComponent;
class UEndNavModifierComponent;
class UStaticMeshComponent;

UCLASS(Blueprintable)
class AEndFieldActionActorBenchBreak : public AEndFieldActionStateManagedActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName FieldActionMenuTextID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float CustomFadeTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AutoSetStoryFlagWhenIconSuggesstionArea;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* PressVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNavModifierComponent* ModifierVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UStaticMeshComponent* BenchMeshComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndSkeletalMeshActor> ZabutonActorClass;
    
    AEndFieldActionActorBenchBreak(const FObjectInitializer& ObjectInitializer);

};

