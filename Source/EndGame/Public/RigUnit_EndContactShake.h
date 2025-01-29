#pragma once
#include "CoreMinimal.h"
#include "Units/Highlevel/RigUnit_HighlevelBase.h"
#include "RigUnit_EndContactShake_Cache.h"
#include "RigUnit_EndContactShake_DebugSettings.h"
#include "RigUnit_EndContactShake_Settings.h"
#include "RigUnit_EndContactShake.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndContactShake : public FRigUnit_HighlevelBaseMutable {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndContactShake_Settings Settings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndContactShake_DebugSettings DebugSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndContactShake_Cache Cache;
    
    ENDGAME_API FRigUnit_EndContactShake();
};

