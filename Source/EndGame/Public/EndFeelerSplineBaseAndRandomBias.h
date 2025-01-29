#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndFeelerSplineBaseAndRandomBias.generated.h"

USTRUCT(BlueprintType)
struct FEndFeelerSplineBaseAndRandomBias {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Base;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D RandomBiasRange;
    
    ENDGAME_API FEndFeelerSplineBaseAndRandomBias();
};

