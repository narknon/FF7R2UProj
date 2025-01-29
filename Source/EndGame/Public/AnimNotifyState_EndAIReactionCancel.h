#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EEndAIEnemyReactionCancel.h"
#include "AnimNotifyState_EndAIReactionCancel.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class UAnimNotifyState_EndAIReactionCancel : public UAnimNotifyState {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndAIEnemyReactionCancel> NotifyTypes;
    
public:
    UAnimNotifyState_EndAIReactionCancel();

};

