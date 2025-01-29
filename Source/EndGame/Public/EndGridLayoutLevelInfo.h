#pragma once
#include "CoreMinimal.h"
#include "EndGridLayoutLevelInfo.generated.h"

class UWorld;

USTRUCT(BlueprintType)
struct FEndGridLayoutLevelInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSoftObjectPtr<UWorld> GridLayoutLevel;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 GridX;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 GridY;
    
    ENDGAME_API FEndGridLayoutLevelInfo();
};

