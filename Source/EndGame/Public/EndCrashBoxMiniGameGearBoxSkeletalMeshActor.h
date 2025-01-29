#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "EEndCrashBoxMiniGameBoxType.h"
#include "EEndCrashBoxMiniGameGearBoxSkeletalMeshActorDifficultyType.h"
#include "EEndCrashBoxMiniGameGearBoxSkeletalMeshActorEffect.h"
#include "EndEnvironmentSkeletalMeshActor.h"
#include "EndCrashBoxMiniGameGearBoxSkeletalMeshActor.generated.h"

class AActor;
class UFXSystemAsset;
class UPrimitiveComponent;
class USQEXSEADSound;
class USceneComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndCrashBoxMiniGameGearBoxSkeletalMeshActor : public AEndEnvironmentSkeletalMeshActor {
    GENERATED_BODY()
public:
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
    EEndCrashBoxMiniGameGearBoxSkeletalMeshActorDifficultyType m_BoxGimmickDifficultyType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_LockCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UFXSystemAsset* m_Effect;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USceneComponent* m_EffectDummyPoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    USQEXSEADSound* HitSoundAsset;
    
public:
    AEndCrashBoxMiniGameGearBoxSkeletalMeshActor(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetImpulseRadius(float InRadius);
    
private:
    UFUNCTION(BlueprintCallable)
    void SetEffectDummyPoint(EEndCrashBoxMiniGameGearBoxSkeletalMeshActorEffect Type, USceneComponent* Component);
    
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
    
};

