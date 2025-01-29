#pragma once
#include "CoreMinimal.h"
#include "RigUnit_EndLipSyncAudioExpression_DebugSettings.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndLipSyncAudioExpression_DebugSettings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnabled;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AudioPower;
    
    ENDGAME_API FRigUnit_EndLipSyncAudioExpression_DebugSettings();
};

