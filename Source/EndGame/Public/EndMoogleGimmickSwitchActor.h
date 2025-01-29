#pragma once
#include "CoreMinimal.h"
#include "EndEnvironmentSkeletalMeshActor.h"
#include "EndMoogleGimmickSwitchActor.generated.h"

class AEndMoogleCaptureGimmick;

UCLASS(Blueprintable)
class AEndMoogleGimmickSwitchActor : public AEndEnvironmentSkeletalMeshActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<AEndMoogleCaptureGimmick> TargetGimmick;
    
    AEndMoogleGimmickSwitchActor(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void PlayAnim(FName AnimName);
    
};

