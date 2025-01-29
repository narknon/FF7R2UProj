#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifySoundAliasResetOrderCache.generated.h"

class USQEXSEADSoundAliasNameSetting;

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifySoundAliasResetOrderCache : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSoftObjectPtr<USQEXSEADSoundAliasNameSetting> AliasSoundNameSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName OrderName;
    
    UEndAnimNotifySoundAliasResetOrderCache();

};

