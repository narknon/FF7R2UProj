#pragma once
#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "EndActorBaseInterface.h"
#include "EndActorInterface.h"
#include "EndCharacterResidentEffect.h"
#include "EndStaticMeshActorBase.generated.h"

class UEndDeformAnimationComponent;
class UEndFlowMapAnimationComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndStaticMeshActorBase : public AStaticMeshActor, public IEndActorInterface, public IEndActorBaseInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndDeformAnimationComponent* DeformAnimationComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFlowMapAnimationComponent* FlowMapAnimationComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndCharacterResidentEffect> ResidentEffects;
    
    AEndStaticMeshActorBase(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

