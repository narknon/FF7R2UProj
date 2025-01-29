#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EAttachBarretSunglassAnimation.h"
#include "EndAnimNotifyBarretSunglasses.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndAnimNotifyBarretSunglasses : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAttachBarretSunglassAnimation AttachSunglasses;
    
    UEndAnimNotifyBarretSunglasses();

};

