#pragma once
#include "CoreMinimal.h"
#include "Units/Highlevel/RigUnit_HighlevelBase.h"
#include "RigUnit_EndBodySpline_Cache.h"
#include "RigUnit_EndBodySpline_DebugSettings.h"
#include "RigUnit_EndBodySpline_Settings.h"
#include "RigUnit_EndBodySpline.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndBodySpline : public FRigUnit_HighlevelBaseMutable {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndBodySpline_Settings Settings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Weight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndBodySpline_DebugSettings DebugSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndBodySpline_Cache Cache;
    
    ENDGAME_API FRigUnit_EndBodySpline();
};

