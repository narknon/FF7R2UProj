#pragma once
#include "CoreMinimal.h"
#include "OptionSelectInfo.generated.h"

USTRUCT(BlueprintType)
struct FOptionSelectInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FString> ValueTexts;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FString> ValueHelps;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> OpenFlags;
    
    ENDGAME_API FOptionSelectInfo();
};

