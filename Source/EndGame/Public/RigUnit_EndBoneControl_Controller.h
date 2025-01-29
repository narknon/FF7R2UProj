#pragma once
#include "CoreMinimal.h"
#include "Rigs/RigHierarchyDefines.h"
#include "RigUnit_EndBoneControl_Controller.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndBoneControl_Controller {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigElementKey ControlItem;
    
    ENDGAME_API FRigUnit_EndBoneControl_Controller();
};

