#pragma once
#include "CoreMinimal.h"
#include "Units/Highlevel/RigUnit_HighlevelBase.h"
#include "UObject/NoExportTypes.h"
#include "RigUnit_EndLookAt_Cache.h"
#include "RigUnit_EndLookAt_DebugSettings.h"
#include "RigUnit_EndLookAt_Settings.h"
#include "RigUnit_EndLookAt.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndLookAt : public FRigUnit_HighlevelBaseMutable {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndLookAt_Settings Settings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Weight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndLookAt_DebugSettings DebugSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bActiveSaccade;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector SaccadeTargetLocation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndLookAt_Cache Cache;
    
    ENDGAME_API FRigUnit_EndLookAt();
};

