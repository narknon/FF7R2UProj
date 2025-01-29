#pragma once
#include "CoreMinimal.h"
#include "Units/Highlevel/RigUnit_HighlevelBase.h"
#include "RigUnit_EndFootControl_Cache.h"
#include "RigUnit_EndFootControl_DebugSettings.h"
#include "RigUnit_EndFootControl_Settings.h"
#include "RigUnit_EndFootControlDefault.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndFootControlDefault : public FRigUnit_HighlevelBaseMutable {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndFootControl_Settings Settings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Weight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndFootControl_DebugSettings DebugSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndFootControl_Cache Cache;
    
    ENDGAME_API FRigUnit_EndFootControlDefault();
};

