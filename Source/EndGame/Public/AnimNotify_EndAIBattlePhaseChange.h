#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_EndAIBattlePhaseChange.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UAnimNotify_EndAIBattlePhaseChange : public UAnimNotify {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> ApplyPhase;
    
public:
    UAnimNotify_EndAIBattlePhaseChange();

};

