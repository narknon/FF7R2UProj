#pragma once
#include "CoreMinimal.h"
#include "EndBikeAIHelicopterLockOnInfo.h"
#include "EndBikeAIHelicopterLockOnInfoList.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeAIHelicopterLockOnInfoList {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisableCreateLockOnEffect;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBikeAIHelicopterLockOnInfo> InfoList;
    
    ENDGAME_API FEndBikeAIHelicopterLockOnInfoList();
};

