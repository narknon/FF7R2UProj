#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndBehaviorJumpExtraActionInput.h"
#include "EndBehaviorFallJumpExtraActionInput.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorFallJumpExtraActionInput : public FEndBehaviorJumpExtraActionInput {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bSetRotation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRotator RootRotation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RotationInterpSpeed;
    
    ENDGAME_API FEndBehaviorFallJumpExtraActionInput();
};

