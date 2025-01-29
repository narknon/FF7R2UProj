#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndAINotifyStartEndType.h"
#include "AnimNotify_EndAIActionRequestActionChild.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UAnimNotify_EndAIActionRequestActionChild : public UAnimNotify {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAINotifyStartEndType NotifyType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ChildActionId;
    
public:
    UAnimNotify_EndAIActionRequestActionChild();

};

