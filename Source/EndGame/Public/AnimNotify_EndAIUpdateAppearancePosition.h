#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndAIUpdateAppearancePositionType.h"
#include "AnimNotify_EndAIUpdateAppearancePosition.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UAnimNotify_EndAIUpdateAppearancePosition : public UAnimNotify {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIUpdateAppearancePositionType NotifyType;
    
public:
    UAnimNotify_EndAIUpdateAppearancePosition();

};

