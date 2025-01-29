#pragma once
#include "CoreMinimal.h"
#include "EndFieldSimpleInteractAnimSetting.h"
#include "EndFieldSimpleInteractPluginBehaviorBase.h"
#include "EndFieldSimpleInteractPluginBodyMotion.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndFieldSimpleInteractPluginBodyMotion : public UEndFieldSimpleInteractPluginBehaviorBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldSimpleInteractAnimSetting> AnimationSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bAllPlayedToComplete;
    
    UEndFieldSimpleInteractPluginBodyMotion();

};

