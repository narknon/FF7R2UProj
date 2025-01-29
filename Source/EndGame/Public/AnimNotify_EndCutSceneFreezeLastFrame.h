#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_EndCutSceneFreezeLastFrame.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UAnimNotify_EndCutSceneFreezeLastFrame : public UAnimNotify {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisableFreezeCamera;
    
public:
    UAnimNotify_EndCutSceneFreezeLastFrame();

};

