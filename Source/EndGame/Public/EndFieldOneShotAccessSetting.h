#pragma once
#include "CoreMinimal.h"
#include "EndFieldOneShotAccessAnimUnit.h"
#include "EndFieldOneShotAccessSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldOneShotAccessSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldOneShotAccessAnimUnit> AnimationUnits;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLastAnimIsLoop;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLastAnimIsKeep;
    
    ENDGAME_API FEndFieldOneShotAccessSetting();
};

