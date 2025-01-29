#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndCameraLockNotify.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndCameraLockNotify : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LockTime;
    
    UEndCameraLockNotify();

};

