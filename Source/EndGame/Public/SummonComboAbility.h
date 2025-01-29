#pragma once
#include "CoreMinimal.h"
#include "SummonComboAbility.generated.h"

USTRUCT(BlueprintType)
struct FSummonComboAbility {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ComboID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> AbilityList;
    
    ENDGAME_API FSummonComboAbility();
};

