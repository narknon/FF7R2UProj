#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EEndChocoboPlayerMoveState.h"
#include "EndAnimNotifyStateModifyPartyChocoboPlayRate.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class ENDGAME_API UEndAnimNotifyStateModifyPartyChocoboPlayRate : public UAnimNotifyState {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<EEndChocoboPlayerMoveState, float> PlayRateMap;
    
public:
    UEndAnimNotifyStateModifyPartyChocoboPlayRate();

};

