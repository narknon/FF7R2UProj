#pragma once
#include "CoreMinimal.h"
#include "SummonChooseAbility.generated.h"

USTRUCT(BlueprintType)
struct FSummonChooseAbility {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ChooseID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> AbilityList;
    
    ENDGAME_API FSummonChooseAbility();
};

