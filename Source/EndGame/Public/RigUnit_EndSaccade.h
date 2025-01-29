#pragma once
#include "CoreMinimal.h"
#include "Units/Highlevel/RigUnit_HighlevelBase.h"
#include "UObject/NoExportTypes.h"
#include "RigUnit_EndSaccade_Cache.h"
#include "RigUnit_EndSaccade_DebugSettings.h"
#include "RigUnit_EndSaccade_Settings.h"
#include "RigUnit_EndSaccade.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndSaccade : public FRigUnit_HighlevelBaseMutable {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndSaccade_Settings Settings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bActiveSaccade;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector SaccadeTargetLocation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Weight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndSaccade_DebugSettings DebugSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndSaccade_Cache Cache;
    
    ENDGAME_API FRigUnit_EndSaccade();
};

