#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldMonkeyBarGameInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldMonkeyBarGameInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector From;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector To;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int16 Index;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int16 BarHeightIndex;
    
    ENDGAME_API FEndFieldMonkeyBarGameInfo();
};

