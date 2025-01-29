#pragma once
#include "CoreMinimal.h"
#include "Units/Highlevel/RigUnit_HighlevelBase.h"
#include "RigUnit_EndLipSyncAudioExpression_Cache.h"
#include "RigUnit_EndLipSyncAudioExpression_DebugSettings.h"
#include "RigUnit_EndLipSyncAudioExpression_Settings.h"
#include "RigUnit_EndLipSyncAudioExpression.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndLipSyncAudioExpression : public FRigUnit_HighlevelBaseMutable {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndLipSyncAudioExpression_Settings Settings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndLipSyncAudioExpression_DebugSettings DebugSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndLipSyncAudioExpression_Cache Cache;
    
    ENDGAME_API FRigUnit_EndLipSyncAudioExpression();
};

