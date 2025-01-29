#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndAIEnemyCancel.h"
#include "AnimNotify_EndAIEnemyCancel.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UAnimNotify_EndAIEnemyCancel : public UAnimNotify {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIEnemyCancel NotifyType;
    
public:
    UAnimNotify_EndAIEnemyCancel();

};

