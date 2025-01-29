#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EActorMoveMode.h"
#include "EndAnimNotifyCharacterMindMoveMode.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyCharacterMindMoveMode : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EActorMoveMode MoveMode;
    
    UEndAnimNotifyCharacterMindMoveMode();

};

