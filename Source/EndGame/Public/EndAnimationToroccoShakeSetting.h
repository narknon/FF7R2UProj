#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndAnimationToroccoShakeSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndAnimationToroccoShakeSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableThisToroccoShake;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector ToroccoShakingSize;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MinToroccoShakingCadence;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaxToroccoShakingCadence;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MinToroccoShakingSustatinTime;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaxToroccoShakingSustatinTime;
    
    ENDGAME_API FEndAnimationToroccoShakeSetting();
};

