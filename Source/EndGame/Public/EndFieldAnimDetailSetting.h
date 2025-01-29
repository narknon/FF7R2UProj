#pragma once
#include "CoreMinimal.h"
#include "EndFieldActorAnimDetailUnit.h"
#include "EndFieldAnimDetailSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldAnimDetailSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldActorAnimDetailUnit> AnimationUnits;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLastAnimIsLoop;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLastAnimIsKeep;
    
    ENDGAME_API FEndFieldAnimDetailSetting();
};

