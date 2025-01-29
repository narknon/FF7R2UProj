#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndBattleHiddenCharacterNotify.generated.h"

UCLASS(Blueprintable, CollapseCategories, Deprecated, NotPlaceable)
class UDEPRECATED_EndBattleHiddenCharacterNotify : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Hidden;
    
    UDEPRECATED_EndBattleHiddenCharacterNotify();

};

