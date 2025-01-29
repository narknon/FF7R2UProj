#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EndDataObjectBattleDamageSourceAccessor.h"
#include "EndDataObjectBattleDamageSourceBlueprint.generated.h"

UCLASS(Blueprintable)
class UEndDataObjectBattleDamageSourceBlueprint : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UEndDataObjectBattleDamageSourceBlueprint();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetTypeParameter(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetTargetOffsetZ(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetTargetOffsetY(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetTargetOffsetX(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetTargetOffsetDirectionType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetTargetName(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetTargetBase(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetTakeDamageDirectionType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetSyncActionHitCountType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetStunValue(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetStunTimeType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetStunAttenuationValueType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetStunAttenuationStartTimeType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetStatusChangeTimeSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetStatusChangeTime(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetStatusChangeProbabilitySize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetStatusChangeProbability(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetStatusChangeLockSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetStatusChangeLock(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetStatusChangeIDSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetStatusChangeID(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetSpecialStatusChangeID(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetShieldType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetRotationType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetReflectType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetRecalcMoveDir(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetRandomBreadth(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetPushCollisionRadiusReachTime(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetPushCollisionEnable(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetProperty(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetProgressDirectionType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetPowerType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetPowerCactusMission(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetPowerBurst(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetPowerBreak(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetPower(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetPhysicsVelocityScaleDamageSource(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetPhysicsVelocityScaleCharacter(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetPhysicsVelocityScaleBackground(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetPhysicsType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetOwnerStopType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetMoveOnTerrain(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetLinkageAddCoefficient(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetLifeTimeNotify(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetLifeTime(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetKnockbackDirType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetKnockbackDirStringParam0(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitTarget6(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitTarget5(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitTarget4(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitTarget3(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitTarget2(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitTarget1(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitTarget0(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetHitSoundResourceName(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitSoundResourceCategory(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetHitSlowID(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetHitReactionTypeSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitReactionType(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetHitReactionParamSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetHitReactionParamIDSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetHitReactionParamID(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0, int32 index1);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetHitReactionParam(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0, int32 index1);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetHitReactionID(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetHitInterval(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetHitGroupName(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetHitForceFeedbackFileName(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitExecutionType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetHitEffectResourceNameSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetHitEffectResourceName(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetHitEffectResourceCategorySize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitEffectResourceCategory(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetHitEffectIntervalTimeSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetHitEffectIntervalTime(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetHitEffectAttachHitLocationSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitEffectAttachHitLocation(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetHitEffectAttachCharacterSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitEffectAttachCharacter(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitDestroyType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitDestroyTargetType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitDamageSourceTypeBit(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetHitDamageSourceIDSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetHitDamageSourceID(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitDamageSourceEffectType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitCountTotal(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitCount(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetHitCharaSpecID(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetHitCameraShakeDataID(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetHitBonusType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetHitBonusParameter(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetHitBonusLimit(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetGuardSoundResourceName(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetGuardSoundResourceCategory(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetGuardOwnerReactionUCPCGuardOnly(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetGuardOwnerReactionType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetGuardOwnerReactionStringParamSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetGuardOwnerReactionStringParam(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetGuardOwnerReactionParamSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetGuardOwnerReactionParam(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetGuardEffectResourceName(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetGuardEffectResourceCategory(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetGuardBasePos(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetForceDamageDisplayToOne(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintPure)
    static int64 GetFlag0(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetExtControlTypeSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetExtControlType(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetExtControlParameterSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetExtControlParameter(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0, int32 index1);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetExtControlNameSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetExtControlName(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0, int32 index1);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetExtControlFlagSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetExtControlFlag(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetEnemyHitCategoryTypeBit(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetDisableMoveHitPosition(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetDisableLookAtCheck(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetDisableHitTime(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetDisableHitOnlyTime(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetDisableHitBackground(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetDirectionType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetDestroyDelayTime(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetDestroyBreakableDamage(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetDangerRange(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetDangerLengthCoefficient(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetDangerDamageReflectType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetDangerDamageDodgeDirectionType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetDangerDamageDestroyDelayTime(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetDamageType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetDamageBlockType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetCutValue(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetCriticalHitRate(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetCreateSoundResourceName(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetCreateSoundResourceCategory(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetCreatePhysicsObjectPartName(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetCreatePhysicsObjectForceRandom(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetCreatePhysicsObjectForce(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetCreatePhysicsObjectDelay(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetCreatePhysicsObjectCharaSpecID(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetCreatePhysicsObjectBasePos(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetCreatePartOffsetZ(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetCreatePartOffsetYaw(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetCreatePartOffsetY(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetCreatePartOffsetX(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetCreatePartOffsetRoll(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetCreatePartOffsetPitch(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetCreatePartOffsetDirectionType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetCreatePartName(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetCreateExecutionType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetCreateEffectResourceName(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetCreateEffectResourceCategory(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetCreateDelayTime(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetCreateDamageSourceParameterSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetCreateDamageSourceParameter(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetCreateDamageSourceFloatSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetCreateDamageSourceFloat(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetCreateDamageSourceConditionTypeSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetCreateDamageSourceConditionType(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetCreateCameraShakeDataID(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetCreateBasePos(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetControlType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetControlParameterSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetControlParameter(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetControlNameSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetControlName(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetControlFlag(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetConditionCreateDamageSourceTypeSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetConditionCreateDamageSourceType(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetConditionCreateDamageSourceIDSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetConditionCreateDamageSourceID(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetCollisionType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetCollisionParameterSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetCollisionParameter(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetCollisionFaceGuardScale(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetCharaSpecType(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetCharaSpecMotionName(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetCharaSpecID(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetBurstTimeExtension(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetBurstHitBonusParameter(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetBurstDamageCoefficientAddOnBurst(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetBreakValue(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetBreakHitBonusParameter(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetBPAttackDamageCoefficient(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetBPAttack(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetBindSoundResourceName(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetBindSoundResourceCategory(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetBindEffectResourceName(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetBindEffectResourceCategory(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetBindEffectOffsetZ(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetBindEffectOffsetYaw(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetBindEffectOffsetY(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetBindEffectOffsetX(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetBindEffectOffsetRoll(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetBindEffectOffsetPitch(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetBindEffectDelayTime(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetBindEffectAttachSocket(const FEndDataObjectBattleDamageSourceAccessor& Instance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetAttributeSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetAttribute(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetAerialHitReactionParamSize(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 dimension);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetAerialHitReactionParam(const FEndDataObjectBattleDamageSourceAccessor& Instance, int32 index0, int32 index1);
    
};

