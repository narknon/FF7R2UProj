#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndMenuImagePathMapping.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndMenuImagePathMapping {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MappingName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSoftObjectPath ImagePath;
    
    FEndMenuImagePathMapping();
};

