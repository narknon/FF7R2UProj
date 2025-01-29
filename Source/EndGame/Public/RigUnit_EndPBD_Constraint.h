#pragma once
#include "CoreMinimal.h"
#include "RigUnit_EndPBD_Constraint.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndPBD_Constraint {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 ConstraintOrder;
    
    ENDGAME_API FRigUnit_EndPBD_Constraint();
};

