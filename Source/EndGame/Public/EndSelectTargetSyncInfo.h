#pragma once
#include "CoreMinimal.h"
#include "EndSelectTargetSyncInfo.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndSelectTargetSyncInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SyncVFXPackName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SyncMaxVFXName;
    
    FEndSelectTargetSyncInfo();
};

