#pragma once
#include "CoreMinimal.h"
#include "EndSyncPoseSkeletalMeshComponent.h"
#include "EndWeaponSyncPoseSkeletalMeshComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndWeaponSyncPoseSkeletalMeshComponent : public UEndSyncPoseSkeletalMeshComponent {
    GENERATED_BODY()
public:
    UEndWeaponSyncPoseSkeletalMeshComponent(const FObjectInitializer& ObjectInitializer);

};

