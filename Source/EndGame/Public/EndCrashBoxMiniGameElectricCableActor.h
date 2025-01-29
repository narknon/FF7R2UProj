#pragma once
#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "EEndCrashBoxMiniGameCableDifficultyType.h"
#include "EEndCrashBoxMiniGameCableType.h"
#include "EEndCrashBoxMiniGameEffectCable.h"
#include "EndStaticMeshActor.h"
#include "EndCrashBoxMiniGameElectricCableActor.generated.h"

class AActor;
class UFXSystemAsset;
class UPrimitiveComponent;
class USceneComponent;
class UStaticMeshComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndCrashBoxMiniGameElectricCableActor : public AEndStaticMeshActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndCrashBoxMiniGameCableType m_CableType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_GroupIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndCrashBoxMiniGameCableDifficultyType m_CableGimmickDifficultyType;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    UFXSystemAsset* m_Effect[15];
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UStaticMeshComponent* m_MainStaticMeshComponent;
    
    UPROPERTY(EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UStaticMeshComponent* m_StaticMeshComponent[11];
    
    UPROPERTY(EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UStaticMeshComponent* m_StaticMeshTriggerComponent[11];
    
    UPROPERTY(EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USceneComponent* m_EffectDummyPoint[15];
    
public:
    AEndCrashBoxMiniGameElectricCableActor(const FObjectInitializer& ObjectInitializer);

private:
    UFUNCTION(BlueprintCallable)
    void SetReferenceStaticMeshTrigger(EEndCrashBoxMiniGameCableType Type, UStaticMeshComponent* StaticMeshComp);
    
    UFUNCTION(BlueprintCallable)
    void SetReferenceStaticMesh(EEndCrashBoxMiniGameCableType Type, UStaticMeshComponent* StaticMeshComp);
    
    UFUNCTION(BlueprintCallable)
    void SetReferenceMainStaticMesh(UStaticMeshComponent* StaticMeshComp);
    
    UFUNCTION(BlueprintCallable)
    void SetEffectDummyPoint(EEndCrashBoxMiniGameEffectCable Type, USceneComponent* Component);
    
    UFUNCTION(BlueprintCallable)
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    EEndCrashBoxMiniGameCableType GetBoxType();
    
    UFUNCTION(BlueprintCallable)
    EEndCrashBoxMiniGameCableType ApplyCableType();
    
};

