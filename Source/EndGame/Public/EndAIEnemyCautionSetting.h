#pragma once
#include "CoreMinimal.h"
#include "EndAIEnemyCautionAnimationSetting.h"
#include "EndAIEnemyCautionMoveSetting.h"
#include "EndAIMoveDefinitionMoveApproach.h"
#include "EndAIEnemyCautionSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndAIEnemyCautionSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAIEnemyCautionMoveSetting MoveSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIEnemyCautionAnimationSetting> AnimiationSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAIMoveDefinitionMoveApproach MoveSettingFromCaution;
    
    ENDGAME_API FEndAIEnemyCautionSetting();
};

