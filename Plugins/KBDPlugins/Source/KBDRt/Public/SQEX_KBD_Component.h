#pragma once
#include "CoreMinimal.h"
#include "ESQEX_Bonamik_PropagationMode.h"
#include "SQEX_BonamikWind_Desc.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "Components/SceneComponent.h"
#include "SQEX_KBD_Component.generated.h"

class UCharacterMovementComponent;
class UObject;
class USQEX_BonamikWind_Asset;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class KBDRT_API USQEX_KBD_Component : public USceneComponent {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UCharacterMovementComponent* CharacterMovementComponent;
    
public:
    USQEX_KBD_Component(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SQEX_KineDriver_SetParam(TMap<FName, float> Params);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_KineDriver_SetEnableBone(bool NewEnable, FName BoneName, float PauseRate, bool bApplyBonamik, bool bApplyChildren);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_KineDriver_SetEnable(bool NewEnable, FName NewLabel);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool SQEX_KineDriver_IsEnable() const;
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_TurnOn(const TArray<FName>& Groups, float BlendTime);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_TurnOff(bool preserveLatestResult, const TArray<FName>& Groups, float BlendTime);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetWorldWindScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetWeight(float Weight, float WeightChangeTime, bool ResetWhenNonZeroWeight, bool AutoDisable);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetSpeedRate(float SpeedRate, float SpeedRateChangeTime, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetPreRoll(int32 Step, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetParkRateScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetOuterConeScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetMassScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetLocalForceScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetInnerConeScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetGroupWeight(const TArray<FName>& Groups, float Weight, float WeightChangeTime, bool ResetWhenNonZeroWeight);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetGroupFrozenState(const TArray<FName>& Groups, bool IsFrozen);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetGravity(const FVector& Gravity);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetFrozenState(bool IsFrozen);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetEnsemble(FName NewEnsemble);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetEnableGroundCollisionAll(bool bNewEnable);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetEnableGroundCollision(const TArray<FName>& Groups, bool bNewEnable);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetEnableExternalColliders(const TArray<FName>& Groups, bool V);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetEnable(bool NewEnable);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetChainRootTransDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetChainRootRotDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetChainRootImpulseScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetChainRootFictitiousForceScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetChainRootCentrifugalScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetBodyVelocityDampingScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetBodyRadiusScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetBodyLiftScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetBodyGravityScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetBodyFrictionScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetBodyDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetBodyDampingScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetBodyConstraintDampingScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetAutoDisable(bool AutoDisable);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetActorTransDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetActorRotDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetActorImpulseScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetActorFictitiousForceScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetActorCentrifugalScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetAccurateGroundCollisionAll(bool V);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_RestoreDefaultParameters();
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_ResetGravity();
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_Reset(bool bResetPose, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_RemoveWorldWindModifier(USceneComponent* Component, UObject* Outer);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_RemoveWind(USceneComponent* Component, UObject* Outer);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_ReinitializeSimulationPose();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool SQEX_Bonamik_IsEnable() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool SQEX_Bonamik_IsAutoDisable() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float SQEX_Bonamik_GetSpeedRate() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 SQEX_Bonamik_GetNumGroups() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FName SQEX_Bonamik_GetGroupName(int32 idx) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector SQEX_Bonamik_GetGravity() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FName SQEX_Bonamik_GetEnsemble() const;
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_Freeze(bool FreezeState, const TArray<FName>& Groups);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_FixedFrameRateThisFrame();
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_AddOrSetWorldWindModifier(USceneComponent* Component, USQEX_BonamikWind_Asset* Wind, float Scale, UObject* Outer);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_AddOrSetWorldWind(USceneComponent* Component, const TArray<FSQEX_BonamikWind_Desc>& Winds, const FTransform& Offset, float Scale, UObject* Outer);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_AddOrSetWindDirect(USceneComponent* Component, const FSQEX_BonamikWind_Desc& Wind, const FTransform& Offset, float Scale, bool bDisableWorldWind, UObject* Outer);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_AddOrSetWind(USceneComponent* Component, USQEX_BonamikWind_Asset* Wind, const FTransform& Offset, float Scale, bool bDisableWorldWind, UObject* Outer);
    
};

