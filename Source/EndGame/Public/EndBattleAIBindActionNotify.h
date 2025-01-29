#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndBattleAIBindActionNotify.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndBattleAIBindActionNotify : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 ID;
    
    UEndBattleAIBindActionNotify();

};

