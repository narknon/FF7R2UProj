#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EActorMoveMode.h"
#include "EndAnimNotifyCharacterBodyMoveMode.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyCharacterBodyMoveMode : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EActorMoveMode MoveMode;
    
    UEndAnimNotifyCharacterBodyMoveMode();

};

