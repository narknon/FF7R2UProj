#pragma once
#include "CoreMinimal.h"
#include "SQEX_AnimNotifyState_Bonamik_TemporaryCollision_ConstraintTransformRules_Vec3.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_AnimNotifyState_Bonamik_TemporaryCollision_ConstraintTransformRules_Vec3 {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bConstraintX;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bConstraintY;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bConstraintZ;
    
    KBDRT_API FSQEX_AnimNotifyState_Bonamik_TemporaryCollision_ConstraintTransformRules_Vec3();
};

