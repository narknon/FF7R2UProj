#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndBikeAIHelicopterSpecificRoadArea.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeAIHelicopterSpecificRoadArea {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SplineID;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FFloatInterval AppliedRange;
    
    ENDGAME_API FEndBikeAIHelicopterSpecificRoadArea();
};

