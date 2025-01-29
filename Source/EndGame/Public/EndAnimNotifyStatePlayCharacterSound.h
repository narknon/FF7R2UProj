#pragma once
#include "CoreMinimal.h"
#include "EndAnimNotifyStatePlaySound.h"
#include "EndAnimNotifyStatePlayCharacterSound.generated.h"

class USoundBase;

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class ENDGAME_API UEndAnimNotifyStatePlayCharacterSound : public UEndAnimNotifyStatePlaySound {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bAutoSE;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDedicatedAction;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundBase* DedicatedActionSound;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundBase* DedicatedActionOnEndSound;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bOverrideFieldActionTargetSound;
    
    UEndAnimNotifyStatePlayCharacterSound();

};

