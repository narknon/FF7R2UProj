#pragma once
#include "CoreMinimal.h"
#include "EndFieldAnimSettingBase.h"
#include "EndFieldLiftingRopeAnimSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldLiftingRopeAnimSetting : public FEndFieldAnimSettingBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndFieldLiftingRopeAnimSetting();
};

