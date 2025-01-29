#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/SceneComponent.h"
#include "ESQEX_Bonamik_PropagationMode.h"
#include "SQEX_Bonamik_Component.generated.h"

class UCharacterMovementComponent;
class USQEX_BonamikAsset;
class USQEX_Bonamik_Component;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class BONAMIKRT_API USQEX_Bonamik_Component : public USceneComponent {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    float fDeltaTime;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEX_BonamikAsset* m_BonamikAsset;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UCharacterMovementComponent* CharacterMovementComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool bEnableGameWind;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool m_BonamikEnable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool m_BonamikAutoDisable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool bAccurateBoundsUpdate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool bPerJointWindSample;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool bForceFrontXAxis;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    int32 PreRollStepOnResume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    float ConstraintDampingAdjustFactor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    float PrevScreenSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    float mTeleportDistance;
    
public:
    USQEX_Bonamik_Component(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_TurnOn(const TArray<FName>& Groups, float BlendTime);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_TurnOff(bool preserveLatestResult, const TArray<FName>& Groups, float BlendTime);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetWorldWindScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetWeight(float Weight, float WeightChangeTime, bool ResetWhenNonZeroWeight, bool AutoDisable);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetTeleportDistance(float Distance, int32 TeleportPreRollStep, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
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
    void SQEX_Bonamik_SetEnableTimestepSmoother(bool V);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetEnableGroundCollisionAll(bool bNewEnable);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetEnableGroundCollision(const TArray<FName>& Groups, bool bNewEnable);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetEnableGameWind(bool Enable);
    
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
    void SQEX_Bonamik_SetChainRootCentrifugalScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetBodyLiftScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetBodyDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetAutoDisable(bool AutoDisable);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetAnimPos(int32 BoneIndex, bool bForceSet);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetActorTransDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetActorRotDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_SetActorImpulseScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode);
    
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
    void SQEX_Bonamik_ReplaceAsset(USQEX_BonamikAsset* originalAsset, USQEX_BonamikAsset* NewAsset);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_RemoveReferenceDefault();
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_RemoveReferenceCommon(USQEX_Bonamik_Component* OtherComponent);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_RemoveReferenceAll();
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_RemoveReference(USQEX_Bonamik_Component* OtherComponent, FName ReferenceGroupName);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_ReinitializeSimulationPose();
    
    UFUNCTION(BlueprintCallable)
    bool SQEX_Bonamik_IsSetup();
    
    UFUNCTION(BlueprintCallable)
    bool SQEX_Bonamik_IsEnable();
    
    UFUNCTION(BlueprintCallable)
    bool SQEX_Bonamik_IsAutoDisable();
    
    UFUNCTION(BlueprintCallable)
    float SQEX_Bonamik_GetWeight();
    
    UFUNCTION(BlueprintCallable)
    float SQEX_Bonamik_GetTeleportDistance();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float SQEX_Bonamik_GetSpeedRate() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 SQEX_Bonamik_GetNumReferences() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 SQEX_Bonamik_GetNumGroups() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FName SQEX_Bonamik_GetGroupName(int32 idx) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector SQEX_Bonamik_GetGravity() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FName SQEX_Bonamik_GetEnsemble() const;
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_Freeze(bool FreezeState, const TArray<FName>& Groups, float BlendTime, float BlendWeight);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_AddReferenceDefault();
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_AddReferenceCommon(USQEX_Bonamik_Component* OtherComponent);
    
    UFUNCTION(BlueprintCallable)
    void SQEX_Bonamik_AddReference(USQEX_Bonamik_Component* OtherComponent, FName ReferenceGroupName);
    
};

