#pragma once
#include "CoreMinimal.h"
#include "Rigs/RigHierarchyDefines.h"
#include "RigUnit_EndContactShake_DebugSettings.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndContactShake_DebugSettings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnabled;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigElementKey TargetItem;
    
    ENDGAME_API FRigUnit_EndContactShake_DebugSettings();
};

