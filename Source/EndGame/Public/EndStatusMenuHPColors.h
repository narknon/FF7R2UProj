#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndStatusMenuHPColors.generated.h"

USTRUCT(BlueprintType)
struct FEndStatusMenuHPColors {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor ChildColor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor ParentColor;
    
    ENDGAME_API FEndStatusMenuHPColors();
};

