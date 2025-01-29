#pragma once
#include "CoreMinimal.h"
#include "EndBikeAITruckGunFireInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeAITruckGunFireInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName DamageSourceID;
    
    ENDGAME_API FEndBikeAITruckGunFireInfo();
};

