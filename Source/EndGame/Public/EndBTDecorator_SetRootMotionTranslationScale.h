#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_DurationBase.h"
#include "EndBTDecorator_SetRootMotionTranslationScale.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_SetRootMotionTranslationScale : public UEndBTDecorator_DurationBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Scale;
    
    UEndBTDecorator_SetRootMotionTranslationScale();

};

