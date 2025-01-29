#pragma once
#include "CoreMinimal.h"
#include "RenoMineAbilityPermissions.generated.h"

USTRUCT(BlueprintType)
struct FRenoMineAbilityPermissions {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> AbilityList;
    
    ENDGAME_API FRenoMineAbilityPermissions();
};

