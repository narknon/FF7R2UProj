#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "Engine/StaticMeshActor.h"
#include "EEndCrashBoxMiniGameBoxDifficultyType.h"
#include "EEndCrashBoxMiniGameBoxType.h"
#include "EEndCrashBoxMiniGameEffect.h"
#include "Templates/SubclassOf.h"
#include "EndCrashBoxMiniGameBoxActor.generated.h"

class AActor;
class AEndCrashBoxMiniGameBoxActor;
class UFXSystemAsset;
class UMaterialParameterLightPlacedComponent;
class UPrimitiveComponent;
class USQEXSEADSound;
class USceneComponent;
class UStaticMeshComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndCrashBoxMiniGameBoxActor : public AStaticMeshActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndCrashBoxMiniGameBoxActor> BonusBoxClass;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndCrashBoxMiniGameBoxType m_BoxType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_bHighGreadL;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_GroupIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_Radius;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_ImpulseStrength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_ImpulseRadius;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndCrashBoxMiniGameBoxDifficultyType m_BoxGimmickDifficultyType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_bPhysicalMagic;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_BonusBoxCount;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    UFXSystemAsset* m_Effect[2];
    
    UPROPERTY(EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UStaticMeshComponent* m_StaticMeshComponent[13];
    
    UPROPERTY(EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USceneComponent* m_EffectDummyPoint[2];
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_EnemyTerritoryId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    USQEXSEADSound* HitSoundAsset;
    
public:
    AEndCrashBoxMiniGameBoxActor(const FObjectInitializer& ObjectInitializer);

private:
    UFUNCTION(BlueprintCallable)
    void SetReferenceStaticMesh(EEndCrashBoxMiniGameBoxType Type, UStaticMeshComponent* StaticMeshComp);
    
    UFUNCTION(BlueprintCallable)
    void SetMaterialParameter(UMaterialParameterLightPlacedComponent* MaterialParameter);
    
public:
    UFUNCTION(BlueprintCallable)
    void SetImpulseRadius(float InRadius);
    
private:
    UFUNCTION(BlueprintCallable)
    void SetEffectDummyPoint(EEndCrashBoxMiniGameEffect Type, USceneComponent* Component);
    
public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetBonusBoxEmissiveMaterial();
    
private:
    UFUNCTION(BlueprintCallable)
    void PlayHitSe_TimerFunc();
    
    UFUNCTION(BlueprintCallable)
    void OnEndImpulseInterval();
    
    UFUNCTION(BlueprintCallable)
    void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
    UFUNCTION(BlueprintCallable)
    bool IsElectricBox();
    
    UFUNCTION(BlueprintCallable)
    void Hit_TimerFunc();
    
public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    EEndCrashBoxMiniGameBoxType GetBoxType();
    
private:
    UFUNCTION(BlueprintCallable)
    void Deactive_TimerFunc();
    
public:
    UFUNCTION(BlueprintCallable)
    EEndCrashBoxMiniGameBoxType ApplyBoxType();
    
};

