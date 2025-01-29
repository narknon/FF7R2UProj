#pragma once
#include "CoreMinimal.h"
#include "EndGroupBoneSetting.h"
#include "EndBoneMovementSeSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndBoneMovementSeSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndGroupBoneSetting> GroupBoneSettings;
    
    ENDGAME_API FEndBoneMovementSeSetting();
};

