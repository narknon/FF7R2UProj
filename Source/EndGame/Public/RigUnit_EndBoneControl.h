#pragma once
#include "CoreMinimal.h"
#include "Units/Highlevel/RigUnit_HighlevelBase.h"
#include "RigUnit_EndBoneControl_Cache.h"
#include "RigUnit_EndBoneControl_DebugSettings.h"
#include "RigUnit_EndBoneControl_Settings.h"
#include "RigUnit_EndBoneControl.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndBoneControl : public FRigUnit_HighlevelBaseMutable {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndBoneControl_Settings Settings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Weight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndBoneControl_DebugSettings DebugSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndBoneControl_Cache Cache;
    
    ENDGAME_API FRigUnit_EndBoneControl();
};

