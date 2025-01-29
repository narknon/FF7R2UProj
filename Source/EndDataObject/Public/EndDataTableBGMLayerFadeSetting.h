#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBGMLayerFadeSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBGMLayerFadeSetting : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> FadeIn_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> FadeOut_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableBGMLayerFadeSetting();
};

