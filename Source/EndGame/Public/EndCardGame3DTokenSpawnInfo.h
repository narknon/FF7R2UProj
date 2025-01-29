#pragma once
#include "CoreMinimal.h"
#include "EndCardGame3DTokenSpawnInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndCardGame3DTokenSpawnInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> Timers;
    
    ENDGAME_API FEndCardGame3DTokenSpawnInfo();
};

