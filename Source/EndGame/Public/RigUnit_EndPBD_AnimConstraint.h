#pragma once
#include "CoreMinimal.h"
#include "Rigs/RigHierarchyDefines.h"
#include "RigUnit_EndPBD_Constraint.h"
#include "RigUnit_EndPBD_AnimConstraint.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndPBD_AnimConstraint : public FRigUnit_EndPBD_Constraint {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRigElementKey Item0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Distance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Stiffness;
    
    ENDGAME_API FRigUnit_EndPBD_AnimConstraint();
};

