#pragma once
#include "CoreMinimal.h"
#include "EEndWireReelState.h"
#include "EndSkeletalMeshActor.h"
#include "EndWireReelActor.generated.h"

class UAnimationAsset;
class UEndBoneAttachComponent;

UCLASS(Blueprintable)
class AEndWireReelActor : public AEndSkeletalMeshActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBoneAttachComponent* BoneAttach;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UAnimationAsset* WireReelAnimToPlay;
    
    AEndWireReelActor(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetWireState(EEndWireReelState InState);
    
};

