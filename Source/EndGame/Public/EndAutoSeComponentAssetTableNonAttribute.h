#pragma once
#include "CoreMinimal.h"
#include "EndAutoSeComponentAssetTableNonAttribute.generated.h"

USTRUCT(BlueprintType)
struct FEndAutoSeComponentAssetTableNonAttribute {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 SoundIndexes[14];
    
    ENDGAME_API FEndAutoSeComponentAssetTableNonAttribute();
};

