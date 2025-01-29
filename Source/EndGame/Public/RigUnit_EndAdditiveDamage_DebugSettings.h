#pragma once
#include "CoreMinimal.h"
#include "Rigs/RigHierarchyDefines.h"
#include "EEndLocomotionState.h"
#include "RigUnit_EndAdditiveDamage_DebugSettings.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndAdditiveDamage_DebugSettings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnabled;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigElementKey HitLocationItem;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndLocomotionState LocomotionState;
    
    ENDGAME_API FRigUnit_EndAdditiveDamage_DebugSettings();
};

