#pragma once
#include "CoreMinimal.h"
#include "BikeEffectInfo.generated.h"

USTRUCT(BlueprintType)
struct FBikeEffectInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName EffectName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SocketName;
    
    ENDGAME_API FBikeEffectInfo();
};

