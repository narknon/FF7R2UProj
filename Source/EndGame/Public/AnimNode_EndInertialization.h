#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNode_Inertialization.h"
#include "AnimNode_EndInertialization.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndInertialization : public FAnimNode_Inertialization {
    GENERATED_BODY()
public:
    FAnimNode_EndInertialization();
};

