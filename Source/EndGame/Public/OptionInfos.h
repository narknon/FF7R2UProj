#pragma once
#include "CoreMinimal.h"
#include "OptionInfo.h"
#include "OptionInfos.generated.h"

USTRUCT(BlueprintType)
struct FOptionInfos {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString HelpText;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FOptionInfo> Infos;
    
    ENDGAME_API FOptionInfos();
};

