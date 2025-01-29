#pragma once
#include "CoreMinimal.h"
#include "EndAutoSeComponentAssetTablePerAttribute.generated.h"

USTRUCT(BlueprintType)
struct FEndAutoSeComponentAssetTablePerAttribute {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 SoundIndexes[8];
    
    ENDGAME_API FEndAutoSeComponentAssetTablePerAttribute();
};

