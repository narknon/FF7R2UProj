#pragma once
#include "CoreMinimal.h"
#include "EEndAnimComponentControlLayer.h"
#include "EEndAnimationCurveType.h"
#include "EEndAnimationModifierType.h"
#include "EndStaticMeshActorBase.h"
#include "EndStaticMeshActor.generated.h"

class UCurveFloat;
class UEndEmissiveColorComponent;
class UEndEmissiveColorSettings;
class UEndMaterialPack;

UCLASS(Blueprintable)
class ENDGAME_API AEndStaticMeshActor : public AEndStaticMeshActorBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndMaterialPack* MaterialPack;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEmissiveColorComponent* EmissiveColorComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndEmissiveColorSettings* OverrideEmissiveColorSettings;
    
    AEndStaticMeshActor(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void StopEmissiveColorAnimation(FName RequestID);
    
    UFUNCTION(BlueprintCallable)
    void SetDirectEmissiveColor(FName RequestID, FName EmissiveColorSettingsId, float IntensityAlpha);
    
    UFUNCTION(BlueprintCallable)
    void ResetDirectEmissiveColor(FName RequestID);
    
    UFUNCTION(BlueprintCallable)
    void PlayEmissiveColorAnimation(FName RequestID, FName EmissiveColorSettingsId, EEndAnimationModifierType ModifierType, EEndAnimationCurveType CurveType, UCurveFloat* CurveAsset, bool bCurveEvaluateInLogarithmicSpace, bool bLoop, float Duration, float RandomAdditiveDuration, float RandomOffset, float BlendInTime, float BlendOutTime, float StartOffset, float EndOffset, EEndAnimComponentControlLayer Layer);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsActiveEmissiveColorAnimation() const;
    
};

