#pragma once
#include "CoreMinimal.h"
#include "EOptionCategory.h"
#include "EOptionSelectionKind.h"
#include "OptionBaseInfo.generated.h"

USTRUCT(BlueprintType)
struct FOptionBaseInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EOptionSelectionKind Kind;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EOptionCategory OptionCategory;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Text;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString HelpText;
    
    ENDGAME_API FOptionBaseInfo();
};

