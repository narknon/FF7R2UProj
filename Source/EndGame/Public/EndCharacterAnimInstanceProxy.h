#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimInstanceProxy.h"
#include "EndCharacterAnimInstanceProxy.generated.h"

USTRUCT(BlueprintType)
struct FEndCharacterAnimInstanceProxy : public FAnimInstanceProxy {
    GENERATED_BODY()
public:
    ENDGAME_API FEndCharacterAnimInstanceProxy();
};

