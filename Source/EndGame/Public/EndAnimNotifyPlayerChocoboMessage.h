#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndAnimNotifyPlayerChocoboMessageType.h"
#include "EndAnimNotifyPlayerChocoboMessage.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyPlayerChocoboMessage : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimNotifyPlayerChocoboMessageType MessageType;
    
    UEndAnimNotifyPlayerChocoboMessage();

};

