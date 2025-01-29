#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EChocoboCraftEvent.h"
#include "EndAnimNotifyChocoboCraftEvent.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyChocoboCraftEvent : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EChocoboCraftEvent ChocoboEvent;
    
    UEndAnimNotifyChocoboCraftEvent();

};

