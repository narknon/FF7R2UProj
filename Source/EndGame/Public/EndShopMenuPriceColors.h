#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndShopMenuPriceColors.generated.h"

USTRUCT(BlueprintType)
struct FEndShopMenuPriceColors {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor Default;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor High;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor Low;
    
    ENDGAME_API FEndShopMenuPriceColors();
};

