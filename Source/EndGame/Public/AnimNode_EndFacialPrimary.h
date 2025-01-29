#pragma once
#include "CoreMinimal.h"
#include "AnimNodes/AnimNode_Slot.h"
#include "AnimNode_EndFacialPrimary.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndFacialPrimary : public FAnimNode_Slot {
    GENERATED_BODY()
public:
    FAnimNode_EndFacialPrimary();
};

