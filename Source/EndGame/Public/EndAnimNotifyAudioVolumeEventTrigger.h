#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifyAudioVolumeEventTrigger.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyAudioVolumeEventTrigger : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AudioVolumeEventID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bUsePrefixOwnerID: 1;
    
    UEndAnimNotifyAudioVolumeEventTrigger();

};

