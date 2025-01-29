#pragma once
#include "CoreMinimal.h"
#include "EndCharacterBase.h"
#include "EndRagdollSEData.h"
#include "EndCharacter.generated.h"

class UAnimSequence;
class UBodyDriver_ArchtypeTuningSet;
class UBodyDriver_BaseDataTuningSet;
class UBodyDriver_BipedBalanceTuningSet;
class UBodyDriver_BipedFallTuningSet;
class UBodyDriver_DebugImpulseTuningSet;
class UBodyDriver_FullBodyBipedIKTuningSet;
class UBodyDriver_ShakeTuningSet;
class UEndBattleTalkCharacterComponent;
class USkeletalMesh;

UCLASS(Blueprintable)
class ENDGAME_API AEndCharacter : public AEndCharacterBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCanFieldAttack;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCreatePhysicsBlockPrimitive;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bOverrideBodyDriverTuningSets;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BaseDataTuningSet* BodyDriverBaseData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BipedFallTuningSet* BodyDriverBipedFall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BipedBalanceTuningSet* BodyDriverBalanceRecovery;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BipedBalanceTuningSet* BodyDriverStaggerfall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_ShakeTuningSet* BodyDriverShakeData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BipedBalanceTuningSet* BodyDriverKnockbackBalance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_FullBodyBipedIKTuningSet* BodyDriverBipedIK;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_DebugImpulseTuningSet* BodyDriverDebugImpulses;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UAnimSequence* BodyDriverIdleAnim;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_ArchtypeTuningSet* BodyDriverArchtypeData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USkeletalMesh* BodyDriverArchtypeSkeletalMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BaseDataTuningSet* BodyDriverArchtypeBaseData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BipedFallTuningSet* BodyDriverArchtypeBipedFall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BipedBalanceTuningSet* BodyDriverArchtypeBalanceRecovery;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_BipedBalanceTuningSet* BodyDriverArchtypeStaggerfall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_ShakeTuningSet* BodyDriverArchtypeShakeData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBodyDriver_DebugImpulseTuningSet* BodyDriverArchtypeDebugImpulses;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UAnimSequence* BodyDriverArchtypeIdleAnim;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndRagdollSEData> RagdollSEData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBattleTalkCharacterComponent* BattleTalkCharacterComponent;
    
    AEndCharacter(const FObjectInitializer& ObjectInitializer);

};

