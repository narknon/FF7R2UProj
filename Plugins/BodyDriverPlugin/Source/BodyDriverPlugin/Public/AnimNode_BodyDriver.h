#pragma once
#include "CoreMinimal.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "AnimNode_BodyDriver.generated.h"

class UAnimSequence;
class UBodyDriver_ArchtypeTuningSet;
class UBodyDriver_BaseDataTuningSet;
class UBodyDriver_BipedBalanceTuningSet;
class UBodyDriver_BipedFallTuningSet;
class UBodyDriver_DebugImpulseTuningSet;
class UBodyDriver_FullBodyBipedIKTuningSet;
class UBodyDriver_ShakeTuningSet;
class UInputObject_BodyDriver;
class USkeletalMesh;

USTRUCT(BlueprintType)
struct BODYDRIVERPLUGIN_API FAnimNode_BodyDriver : public FAnimNode_SkeletalControlBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BaseDataTuningSet* BaseData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BipedFallTuningSet* BipedFall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BipedBalanceTuningSet* BalanceRecovery;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BipedBalanceTuningSet* Staggerfall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_ShakeTuningSet* ShakeData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BipedBalanceTuningSet* KnockbackBalance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_FullBodyBipedIKTuningSet* BipedIK;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_DebugImpulseTuningSet* DebugImpulses;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UAnimSequence* IdleAnim;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_ArchtypeTuningSet* ArchtypeData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USkeletalMesh* ArchtypeSkeletalMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BaseDataTuningSet* ArchtypeBaseData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BipedFallTuningSet* ArchtypeBipedFall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BipedBalanceTuningSet* ArchtypeBalanceRecovery;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BipedBalanceTuningSet* ArchtypeStaggerfall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_ShakeTuningSet* ArchtypeShakeData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_DebugImpulseTuningSet* ArchtypeDebugImpulses;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UAnimSequence* ArchtypeIdleAnim;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UInputObject_BodyDriver* m_InputObject;
    
public:
    FAnimNode_BodyDriver();
};

