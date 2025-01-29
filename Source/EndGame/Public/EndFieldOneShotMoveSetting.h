#pragma once
#include "CoreMinimal.h"
#include "EndFieldOneShotMoveAnimUnit.h"
#include "EndFieldOneShotMoveSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldOneShotMoveSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldOneShotMoveAnimUnit> AnimationUnits;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLastAnimIsLoop;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLastAnimIsKeep;
    
    ENDGAME_API FEndFieldOneShotMoveSetting();
};

