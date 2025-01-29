#pragma once
#include "CoreMinimal.h"
#include "Units/Highlevel/RigUnit_HighlevelBase.h"
#include "RigUnit_EndFitGround_Cache.h"
#include "RigUnit_EndFitGround_DebugSettings.h"
#include "RigUnit_EndFitGround_Settings.h"
#include "RigUnit_EndFitGround.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndFitGround : public FRigUnit_HighlevelBaseMutable {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndFitGround_Settings Settings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Weight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndFitGround_DebugSettings DebugSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndFitGround_Cache Cache;
    
    ENDGAME_API FRigUnit_EndFitGround();
};

