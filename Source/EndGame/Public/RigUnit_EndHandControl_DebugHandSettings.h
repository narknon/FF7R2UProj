#pragma once
#include "CoreMinimal.h"
#include "Rigs/RigHierarchyDefines.h"
#include "RigUnit_EndHandControl_DebugHandSettings.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndHandControl_DebugHandSettings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigElementKey ControlItem;
    
    ENDGAME_API FRigUnit_EndHandControl_DebugHandSettings();
};

