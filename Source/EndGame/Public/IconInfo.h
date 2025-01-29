#pragma once
#include "CoreMinimal.h"
#include "IconInfo.generated.h"

USTRUCT(BlueprintType)
struct FIconInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 iconIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString textName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool notDispel;
    
    ENDGAME_API FIconInfo();
};

