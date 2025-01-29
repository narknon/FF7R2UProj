#pragma once
#include "CoreMinimal.h"
#include "Units/Highlevel/RigUnit_HighlevelBase.h"
#include "RigUnit_EndLookAround_Cache.h"
#include "RigUnit_EndLookAround_DebugSettings.h"
#include "RigUnit_EndLookAround_Settings.h"
#include "RigUnit_EndLookAround.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndLookAround : public FRigUnit_HighlevelBaseMutable {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndLookAround_Settings Settings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Weight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndLookAround_DebugSettings DebugSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndLookAround_Cache Cache;
    
    ENDGAME_API FRigUnit_EndLookAround();
};

