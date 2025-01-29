#pragma once
#include "CoreMinimal.h"
#include "EndAbilityIDBranch.generated.h"

USTRUCT(BlueprintType)
struct FEndAbilityIDBranch {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AbilityId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SoundName;
    
    ENDGAME_API FEndAbilityIDBranch();
};

