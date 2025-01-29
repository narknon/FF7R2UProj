#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndBehaviorJumpExtraActionInput.h"
#include "EndBehaviorNormalJumpExtraActionInput.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorNormalJumpExtraActionInput : public FEndBehaviorJumpExtraActionInput {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bAutoSetVelocity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector Velocity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float JumpZVelocity;
    
    ENDGAME_API FEndBehaviorNormalJumpExtraActionInput();
};

