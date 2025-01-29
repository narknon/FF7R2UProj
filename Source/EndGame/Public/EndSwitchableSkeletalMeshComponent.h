#pragma once
#include "CoreMinimal.h"
#include "EndSwitchableSkeletalMeshPair.h"
#include "EndSyncPoseSkeletalMeshComponent.h"
#include "EndSwitchableSkeletalMeshComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndSwitchableSkeletalMeshComponent : public UEndSyncPoseSkeletalMeshComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndSwitchableSkeletalMeshPair> SkeletalMeshes;
    
    UEndSwitchableSkeletalMeshComponent(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetSkeletalMeshByLabel(FName Label, bool bReinitPose);
    
    UFUNCTION(BlueprintCallable)
    void SetSkeletalMeshByIndex(int32 Index, bool bReinitPose);
    
};

