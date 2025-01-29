#pragma once
#include "CoreMinimal.h"
#include "Units/RigUnit.h"
#include "RigUnit_EndGetIKWeight.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndGetIKWeight : public FRigUnitMutable {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float IKWeight;
    
    ENDGAME_API FRigUnit_EndGetIKWeight();
};

