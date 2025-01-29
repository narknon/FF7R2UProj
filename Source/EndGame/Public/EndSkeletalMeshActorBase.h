#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Animation/SkeletalMeshActor.h"
#include "EEndAnimComponentControlLayer.h"
#include "EEndAnimationCurveType.h"
#include "EEndAnimationModifierType.h"
#include "EEndDeformAnimationType.h"
#include "EndActorBaseInterface.h"
#include "EndActorInterface.h"
#include "EndCharacterResidentEffect.h"
#include "EndSkeletalMeshActorBase.generated.h"

class UAnimSequenceBase;
class UCurveFloat;
class UEndCoordinateAnimationComponent;
class UEndDeformAnimationComponent;
class UEndEmissiveColorComponent;
class UEndEmissiveColorSettings;
class UEndFlowMapAnimationComponent;
class UEndLightAnimationComponent;
class UEndMaterialPack;
class UStaticMesh;
class UStaticMeshComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndSkeletalMeshActorBase : public ASkeletalMeshActor, public IEndActorInterface, public IEndActorBaseInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndMaterialPack* MaterialPack;
    
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
    UStaticMesh* DeformMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndDeformAnimationComponent* DeformAnimationComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UStaticMeshComponent* DeformMeshComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndCharacterResidentEffect> ResidentEffects;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bSteeringObstacle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector SteeringOverridObstacleExtent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector SteeringOverrideObstacleOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SteeringOverrideParamTableId;
    
public:
    AEndSkeletalMeshActorBase(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void StopLightAnimation(FName RequestID);
    
    UFUNCTION(BlueprintCallable)
    void StopFlowMapAnimation();
    
    UFUNCTION(BlueprintCallable)
    void StopEmissiveColorAnimation(FName RequestID);
    
    UFUNCTION(BlueprintCallable)
    void StopDeformAnimation();
    
    UFUNCTION(BlueprintCallable)
    void StopCoordinateAnimation(FName RequestID);
    
    UFUNCTION(BlueprintCallable)
    void SetDirectEmissiveColor(FName RequestID, FName EmissiveColorSettingsId, float IntensityAlpha);
    
    UFUNCTION(BlueprintCallable)
    void ResetDirectEmissiveColor(FName RequestID);
    
    UFUNCTION(BlueprintCallable)
    void PlayLightAnimation(FName RequestID, FName LightAnimationSettingsId, EEndAnimationModifierType ModifierType, EEndAnimationCurveType CurveType, UCurveFloat* CurveAsset, bool bCurveEvaluateInLogarithmicSpace, bool bLoop, float Duration, float RandomAdditiveDuration, float RandomOffset, float BlendInTime, float BlendOutTime, float StartOffset, float EndOffset);
    
    UFUNCTION(BlueprintCallable)
    void PlayFlowMapAnimation(float PlayRate, bool bOverrideConstantParameter, const FVector& ConstantParameter0, const FVector& ConstantParameter1);
    
    UFUNCTION(BlueprintCallable)
    void PlayExtraActionFromAsset(UAnimSequenceBase* Asset, bool bLooping, float BlendInTime, float StartTime);
    
    UFUNCTION(BlueprintCallable)
    void PlayEmissiveColorAnimation(FName RequestID, FName EmissiveColorSettingsId, EEndAnimationModifierType ModifierType, EEndAnimationCurveType CurveType, UCurveFloat* CurveAsset, bool bCurveEvaluateInLogarithmicSpace, bool bLoop, float Duration, float RandomAdditiveDuration, float RandomOffset, float BlendInTime, float BlendOutTime, float StartOffset, float EndOffset, EEndAnimComponentControlLayer Layer);
    
    UFUNCTION(BlueprintCallable)
    void PlayDeformAnimation(EEndDeformAnimationType AnimationType, float StartFrame, const FName& SyncAnimationName, EEndAnimComponentControlLayer Layer);
    
    UFUNCTION(BlueprintCallable)
    void PlayCoordinateAnimation(FName RequestID, FName CoordinateAnimationSettingsId, EEndAnimationCurveType CurveType, bool bLoop, float Duration);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsActiveLightAnimation() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsActiveFlowMapAnimation() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsActiveEmissiveColorAnimation() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsActiveDeformAnimation() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsActiveCoordinateAnimation() const;
    

    // Fix for true pure virtual functions not being implemented
};

