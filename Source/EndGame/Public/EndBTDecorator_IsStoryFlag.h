#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsStoryFlag.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsStoryFlag : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName StoryFlagId;
    
    UEndBTDecorator_IsStoryFlag();

};

