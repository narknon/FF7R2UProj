#pragma once
#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Engine/StaticMeshActor.h"
#include "EEndCrashBoxMiniGameLiftDifficultyType.h"
#include "EEndCrashBoxMiniGameLiftPartsType.h"
#include "Templates/SubclassOf.h"
#include "EndCrashBoxMiniGameLiftRootActor.generated.h"

class AActor;
class AEndCrashBoxMiniGameLiftLeverActor;
class AEndEnvironmentSkeletalMeshActor;
class UPrimitiveComponent;
class UStaticMeshComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndCrashBoxMiniGameLiftRootActor : public AStaticMeshActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndEnvironmentSkeletalMeshActor> LiftClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndEnvironmentSkeletalMeshActor> DownLiftClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndCrashBoxMiniGameLiftLeverActor> LeverClass;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_GroupIndex;
    
    UPROPERTY(EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UStaticMeshComponent* m_StaticMeshComponent[5];
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_bStartUpSide;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_bLiftLongMove;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndCrashBoxMiniGameLiftDifficultyType m_LiftGimmickDifficultyType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_bLiftPartsEnable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_LiftPartsPositionZ;
    
public:
    AEndCrashBoxMiniGameLiftRootActor(const FObjectInitializer& ObjectInitializer);

private:
    UFUNCTION(BlueprintCallable)
    void SetReferenceStaticMesh(EEndCrashBoxMiniGameLiftPartsType Type, UStaticMeshComponent* StaticMeshComp);
    
    UFUNCTION(BlueprintCallable)
    void SetLiftActor(AEndEnvironmentSkeletalMeshActor* LiftActor);
    
    UFUNCTION(BlueprintCallable)
    void SetLeverActor(AEndCrashBoxMiniGameLiftLeverActor* LeverActor);
    
public:
    UFUNCTION(BlueprintCallable)
    void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
private:
    UFUNCTION(BlueprintCallable)
    void LiftPartsInitialize();
    
};

