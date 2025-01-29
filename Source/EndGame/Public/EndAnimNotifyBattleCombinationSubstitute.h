#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifyBattleCombinationSubstitute.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyBattleCombinationSubstitute : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Flag;
    
    UEndAnimNotifyBattleCombinationSubstitute();

};

