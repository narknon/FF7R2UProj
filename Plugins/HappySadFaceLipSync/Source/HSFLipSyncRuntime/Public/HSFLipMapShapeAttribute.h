#pragma once
#include "CoreMinimal.h"
#include "EHSFLipMapShapeAttributeType.h"
#include "HSFLipMapShapeAttribute.generated.h"

USTRUCT(BlueprintType)
struct HSFLIPSYNCRUNTIME_API FHSFLipMapShapeAttribute {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<EHSFLipMapShapeAttributeType, float> Data;
    
    FHSFLipMapShapeAttribute();
};

