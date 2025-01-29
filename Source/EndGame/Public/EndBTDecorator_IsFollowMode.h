#pragma once
#include "CoreMinimal.h"
#include "EEndAIFollowMode.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsFollowMode.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsFollowMode : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndAIFollowMode> m_FollowModes;
    
    UEndBTDecorator_IsFollowMode();

};

