#pragma once
#include "CoreMinimal.h"
#include "EndAnimNotifyPlaySound.h"
#include "EndAnimNotifyPlayCharacterSound.generated.h"

class USoundBase;

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyPlayCharacterSound : public UEndAnimNotifyPlaySound {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bAutoSE;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDedicatedAction;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundBase* DedicatedActionSound;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bOverrideFieldActionTargetSound;
    
    UEndAnimNotifyPlayCharacterSound();

};

