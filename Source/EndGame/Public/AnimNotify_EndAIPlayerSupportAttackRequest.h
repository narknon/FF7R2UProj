#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_EndAIPlayerSupportAttackRequest.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UAnimNotify_EndAIPlayerSupportAttackRequest : public UAnimNotify {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Time;
    
public:
    UAnimNotify_EndAIPlayerSupportAttackRequest();

};

