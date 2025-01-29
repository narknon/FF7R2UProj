#pragma once
#include "CoreMinimal.h"
#include "EndAIEnemyCautionAnimationSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndAIEnemyCautionAnimationSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SequenceName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Weight;
    
    ENDGAME_API FEndAIEnemyCautionAnimationSetting();
};

