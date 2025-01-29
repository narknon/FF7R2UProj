#pragma once
#include "CoreMinimal.h"
#include "Units/Highlevel/RigUnit_HighlevelBase.h"
#include "RigUnit_EndAdditiveDamage_Cache.h"
#include "RigUnit_EndAdditiveDamage_DebugSettings.h"
#include "RigUnit_EndAdditiveDamage_Settings.h"
#include "RigUnit_EndAdditiveDamage.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndAdditiveDamage : public FRigUnit_HighlevelBaseMutable {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndAdditiveDamage_Settings Settings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Weight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndAdditiveDamage_DebugSettings DebugSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigUnit_EndAdditiveDamage_Cache Cache;
    
    ENDGAME_API FRigUnit_EndAdditiveDamage();
};

