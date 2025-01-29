#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EEndDolphinJumpInputButton.h"
#include "EEndDolphinJumpInputEvents.h"
#include "EndAnimNotifyMiniGameDolphinJumpInputEvent.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class ENDGAME_API UEndAnimNotifyMiniGameDolphinJumpInputEvent : public UAnimNotifyState {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndDolphinJumpInputEvents EventType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndDolphinJumpInputButton ButtonType;
    
public:
    UEndAnimNotifyMiniGameDolphinJumpInputEvent();

};

