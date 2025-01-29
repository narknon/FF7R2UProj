#pragma once
#include "CoreMinimal.h"
#include "EndCharacterAbilityCancelStartParameter.generated.h"

USTRUCT(BlueprintType)
struct FEndCharacterAbilityCancelStartParameter {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Number;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Timing;
    
    ENDGAME_API FEndCharacterAbilityCancelStartParameter();
};

