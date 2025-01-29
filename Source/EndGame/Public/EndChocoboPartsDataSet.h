#pragma once
#include "CoreMinimal.h"
#include "EndChocoboPartsData.h"
#include "EndChocoboPartsDataSet.generated.h"

USTRUCT(BlueprintType)
struct FEndChocoboPartsDataSet {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndChocoboPartsData DefaultBody;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndChocoboPartsData EquippedBody;
    
    ENDGAME_API FEndChocoboPartsDataSet();
};

