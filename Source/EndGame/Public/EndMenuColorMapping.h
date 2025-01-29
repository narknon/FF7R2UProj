#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndMenuColorMapping.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndMenuColorMapping {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MappingName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor Color;
    
    FEndMenuColorMapping();
};

