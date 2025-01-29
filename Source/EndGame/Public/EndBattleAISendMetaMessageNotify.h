#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndBattleAISendMetaMessageNotify.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndBattleAISendMetaMessageNotify : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Message;
    
    UEndBattleAISendMetaMessageNotify();

};

