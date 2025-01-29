#pragma once
#include "CoreMinimal.h"
#include "EndSkeletalMeshComponent.h"
#include "EndSwitchableSkeletalMeshPair.h"
#include "EndSwitchableBodySkeletalMeshComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndSwitchableBodySkeletalMeshComponent : public UEndSkeletalMeshComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndSwitchableSkeletalMeshPair> SkeletalMeshes;
    
    UEndSwitchableBodySkeletalMeshComponent(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetSkeletalMeshByLabel(FName Label, bool bReinitPose);
    
    UFUNCTION(BlueprintCallable)
    void SetSkeletalMeshByIndex(int32 Index, bool bReinitPose);
    
};

