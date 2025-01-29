#pragma once
#include "CoreMinimal.h"
#include "Styling/SlateBrush.h"
#include "EndMenuResidentImageMapping.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndMenuResidentImageMapping {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MappingName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSlateBrush Brush;
    
    FEndMenuResidentImageMapping();
};

