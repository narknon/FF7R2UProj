#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Character.h"
#include "EEndAnimComponentControlLayer.h"
#include "EEndAnimationCurveType.h"
#include "EEndAnimationModifierType.h"
#include "EEndVoiceEffectType.h"
#include "EWeaponSlot.h"
#include "EndActorBaseInterface.h"
#include "EndActorInterface.h"
#include "EndAnimSetActorInterface.h"
#include "EndCharacterMovementExpressionSetting.h"
#include "EndCharacterResidentEffect.h"
#include "EndCharacterWeaponSlot.h"
#include "EndInteractorInterface.h"
#include "EndCharacterBase.generated.h"

class AController;
class AEndAIController;
class AEndPlayerController;
class UActorComponent;
class UCurveFloat;
class UEndAIModelTemplateData;
class UEndAutoSeComponentSoundIndexTable;
class UEndBodyControlRig;
class UEndCoordinateAnimationComponent;
class UEndEmissiveColorComponent;
class UEndEmissiveColorSettings;
class UEndFacialControlRig;
class UEndFlowMapAnimationComponent;
class UEndLightAnimationComponent;
class UEndMaterialPack;
class USQEXSEADAutoSeComponentSetting;
class USQEXSEADAutoSeDetectionSetting;
class USQEXSEADAutoSeProcessorLODSettings;
class USoundBase;

UCLASS(Blueprintable)
class ENDGAME_API AEndCharacterBase : public ACharacter, public IEndActorInterface, public IEndActorBaseInterface, public IEndInteractorInterface, public IEndAnimSetActorInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 DitherFadeSettingFlag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OverwriteNearFadeDistance;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AdditionalNearFadeBoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AdditionalNearFadeRadius;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector SteeringBaseLocationOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector OverrideSteeringExtent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName OverrideFieldSteeringParamTableId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName OverrideBattleSteeringParamTableId;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TMap<FName, UActorComponent*> ComponentTable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndPlayerController* PlayerController;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AController* ActiveController;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndAIController* AIController;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TArray<AEndAIController*> AIControllerList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndAIModelTemplateData* AITemplateData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StartSwimmingDepth;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bForceUpdateKinematicBonesUpdateToPhysics;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bAutoSetMeshRelativeLocation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndBodyControlRig* BodyControlRig;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndFacialControlRig* FacialControlRig;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEmissiveColorComponent* EmissiveColorComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndEmissiveColorSettings* OverrideEmissiveColorSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndLightAnimationComponent* LightAnimationComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCoordinateAnimationComponent* CoordinateAnimationComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFlowMapAnimationComponent* FlowMapAnimationComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bForceUpdateAnimation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bOverrideMovementExpressionSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCharacterMovementExpressionSetting MovementExpressionSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool bResidentEffectIgnoreWorldPause;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndCharacterResidentEffect> ResidentEffects;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndCharacterResidentEffect> ResidentFlyEffects;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bStopResidentEffectOnDead;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDontPlayResidentEffectAtStart;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bIgnoreAutoSetCastShadow;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndVoiceEffectType VoiceEffectType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEXSEADAutoSeComponentSetting* SoundSettingData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEXSEADAutoSeDetectionSetting* SoundDetectionSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEXSEADAutoSeProcessorLODSettings* AutoSeProcLodSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndAutoSeComponentSoundIndexTable* SoundIndexTable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnabledFootAttribute;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUpdateFootAttributeWithoutAutoSeSetting;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AutoSeLODIntervalUnit;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndMaterialPack* MaterialPack;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    USoundBase* RandomSoundVoiceResource;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TMap<EWeaponSlot, FEndCharacterWeaponSlot> WeaponSlots;
    
public:
    AEndCharacterBase(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void StopWeaponEmissiveColorAnimation(EWeaponSlot Slot, FName RequestID);
    
    UFUNCTION(BlueprintCallable)
    void StopLightAnimation(FName RequestID);
    
    UFUNCTION(BlueprintCallable)
    void StopFlowMapAnimation();
    
    UFUNCTION(BlueprintCallable)
    void StopEmissiveColorAnimation(FName RequestID);
    
    UFUNCTION(BlueprintCallable)
    void StopCoordinateAnimation(FName RequestID);
    
    UFUNCTION(BlueprintCallable)
    void SetMaterialPack(UEndMaterialPack* InMaterialPack);
    
    UFUNCTION(BlueprintCallable)
    void SetDirectEmissiveColor(FName RequestID, FName EmissiveColorSettingsId, float IntensityAlpha);
    
    UFUNCTION(BlueprintCallable)
    void SetChildMesh(FName MeshName, FName Label);
    
    UFUNCTION(BlueprintCallable)
    void ResetMaterialPack();
    
    UFUNCTION(BlueprintCallable)
    void ResetDirectEmissiveColor(FName RequestID);
    
    UFUNCTION(BlueprintCallable)
    void PlayWeaponEmissiveColorAnimation(EWeaponSlot Slot, FName RequestID, FName EmissiveColorSettingsId, EEndAnimationModifierType ModifierType, EEndAnimationCurveType CurveType, UCurveFloat* CurveAsset, bool bCurveEvaluateInLogarithmicSpace, bool bLoop, float Duration, float RandomAdditiveDuration, float RandomOffset, float BlendInTime, float BlendOutTime, float StartOffset, float EndOffset, EEndAnimComponentControlLayer Layer);
    
    UFUNCTION(BlueprintCallable)
    void PlayLightAnimation(FName RequestID, FName LightAnimationSettingsId, EEndAnimationModifierType ModifierType, EEndAnimationCurveType CurveType, UCurveFloat* CurveAsset, bool bCurveEvaluateInLogarithmicSpace, bool bLoop, float Duration, float RandomAdditiveDuration, float RandomOffset, float BlendInTime, float BlendOutTime, float StartOffset, float EndOffset);
    
    UFUNCTION(BlueprintCallable)
    void PlayFlowMapAnimation(float PlayRate, bool bOverrideConstantParameter, const FVector& ConstantParameter0, const FVector& ConstantParameter1);
    
    UFUNCTION(BlueprintCallable)
    void PlayEmissiveColorAnimation(FName RequestID, FName EmissiveColorSettingsId, EEndAnimationModifierType ModifierType, EEndAnimationCurveType CurveType, UCurveFloat* CurveAsset, bool bCurveEvaluateInLogarithmicSpace, bool bLoop, float Duration, float RandomAdditiveDuration, float RandomOffset, float BlendInTime, float BlendOutTime, float StartOffset, float EndOffset, EEndAnimComponentControlLayer Layer);
    
    UFUNCTION(BlueprintCallable)
    void PlayCoordinateAnimation(FName RequestID, FName CoordinateAnimationSettingsId, EEndAnimationCurveType CurveType, bool bLoop, float Duration);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsPlayer() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsActiveLightAnimation() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsActiveFlowMapAnimation() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsActiveEmissiveColorAnimation() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsActiveCoordinateAnimation() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FRotator GetPointRotationFromOwnPosture(FVector InLocation);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetPointDirectionFromOwnPosture(FVector InLocation);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetFeetLocation() const;
    

    // Fix for true pure virtual functions not being implemented
};

