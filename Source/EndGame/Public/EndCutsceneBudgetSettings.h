#pragma once
#include "CoreMinimal.h"
#include "EndCutsceneBudgetSettings.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndCutsceneBudgetSettings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BudgetSize;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Range;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 MaxMovieNum;
    
    FEndCutsceneBudgetSettings();
};

