#pragma once
#include "CoreMinimal.h"
#include "EndAnimActorDebugFlags.generated.h"

USTRUCT(BlueprintType)
struct FEndAnimActorDebugFlags {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bPauseOnBeginCutScene;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bPauseOnEndCutScene;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bOutputAttachLogs;
    
    ENDGAME_API FEndAnimActorDebugFlags();
};

