#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndBikeSplineMetaData.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeSplineMetaData {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FFloatInterval AppliedRange;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MetaDataTableID;
    
    ENDGAME_API FEndBikeSplineMetaData();
};

