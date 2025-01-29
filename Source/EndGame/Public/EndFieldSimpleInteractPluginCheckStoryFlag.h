#pragma once
#include "CoreMinimal.h"
#include "EndFieldSimpleInteractPluginBase.h"
#include "EndFieldSimpleInteractPluginCheckStoryFlag.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndFieldSimpleInteractPluginCheckStoryFlag : public UEndFieldSimpleInteractPluginBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName StoryFlagName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisalbeStoryFlagNameMatching;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCheckStoryFlagIsOn;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCheckStoryFlagIsOff;
    
    UEndFieldSimpleInteractPluginCheckStoryFlag();

};

