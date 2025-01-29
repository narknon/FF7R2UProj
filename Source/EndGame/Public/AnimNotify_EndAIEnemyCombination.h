#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndAIEnemyCombinationNotify.h"
#include "AnimNotify_EndAIEnemyCombination.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UAnimNotify_EndAIEnemyCombination : public UAnimNotify {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIEnemyCombinationNotify CombinationType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCombiCancelAbility;
    
public:
    UAnimNotify_EndAIEnemyCombination();

};

