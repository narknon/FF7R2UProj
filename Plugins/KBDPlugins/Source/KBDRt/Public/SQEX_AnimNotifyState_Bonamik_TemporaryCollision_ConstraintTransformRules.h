#pragma once
#include "CoreMinimal.h"
#include "SQEX_AnimNotifyState_Bonamik_TemporaryCollision_ConstraintTransformRules_Vec3.h"
#include "SQEX_AnimNotifyState_Bonamik_TemporaryCollision_ConstraintTransformRules.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_AnimNotifyState_Bonamik_TemporaryCollision_ConstraintTransformRules {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEX_AnimNotifyState_Bonamik_TemporaryCollision_ConstraintTransformRules_Vec3 ConstraintLocation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEX_AnimNotifyState_Bonamik_TemporaryCollision_ConstraintTransformRules_Vec3 ConstraintRotation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEX_AnimNotifyState_Bonamik_TemporaryCollision_ConstraintTransformRules_Vec3 ConstraintScale;
    
    KBDRT_API FSQEX_AnimNotifyState_Bonamik_TemporaryCollision_ConstraintTransformRules();
};

