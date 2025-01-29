#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableRecommendedLevel.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableRecommendedLevel : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Level;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 HardLevel;
    
public:
    ENDDATAOBJECT_API FEndDataTableRecommendedLevel();
};

