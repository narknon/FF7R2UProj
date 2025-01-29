#pragma once
#include "CoreMinimal.h"
#include "Units/Highlevel/RigUnit_HighlevelBase.h"
#include "RigUnit_EndPBD_Cache.h"
#include "RigUnit_EndPBD_DebugSettings.h"
#include "RigUnit_EndPBD_Settings.h"
#include "RigUnit_EndPBD.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndPBD : public FRigUnit_HighlevelBaseMutable {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndPBD_Settings Settings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Weight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndPBD_DebugSettings DebugSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndPBD_Cache Cache;
    
    ENDGAME_API FRigUnit_EndPBD();
};

