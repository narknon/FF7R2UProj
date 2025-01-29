#pragma once
#include "CoreMinimal.h"
#include "EndSkeletalMeshComponent.h"
#include "EndSyncPoseSkeletalMeshComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndSyncPoseSkeletalMeshComponent : public UEndSkeletalMeshComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSkeletalMeshComponent* SyncPoseTarget;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SyncPoseRootBoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bAttachParentIsMasterPose: 1;
    
    UEndSyncPoseSkeletalMeshComponent(const FObjectInitializer& ObjectInitializer);

};

