#pragma once
#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EndActorBaseInterface.h"
#include "EndCrowdActorInterface.h"
#include "EndMobCrowdAttachmentGroup.h"
#include "EndMobCrowdGroup.h"
#include "EndOptimizeAnimActorInterface.h"
#include "EndMobCrowdActor.generated.h"

class AEndCharacterBase;
class USkeletalMeshComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndMobCrowdActor : public ATriggerBox, public IEndCrowdActorInterface, public IEndActorBaseInterface, public IEndOptimizeAnimActorInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseMinLOD;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 MinLOD;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bForceCastShadow;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PerformanceModeReductionRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float CameraCutCullingDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> UpdateLODDistanceThresholds;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float GraphicsModeUpdateLODDistanceBias;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName OptimizeTag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndMobCrowdGroup> MobCrowdGroups;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndMobCrowdAttachmentGroup> AttachmentGroups;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<USkeletalMeshComponent*> SkeletalMesheComponents;
    
    AEndMobCrowdActor(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void Stop(float BlendTime, bool bUseFade);
    
    UFUNCTION(BlueprintCallable)
    void SetSkeletalMeshVisibility(int32 Index, bool bVisiblity);
    
    UFUNCTION(BlueprintCallable)
    void SetOverride(FName OverrideName);
    
    UFUNCTION(BlueprintCallable)
    void SetCustomSkeletalMesh(int32 Index, AEndCharacterBase* Character);
    
    UFUNCTION(BlueprintCallable)
    void ResetOverride();
    
    UFUNCTION(BlueprintCallable)
    void Play(float BlendTime, bool bUseFade);
    
    UFUNCTION(BlueprintCallable)
    void OnRefleshCustomSkeletalMesh();
    

    // Fix for true pure virtual functions not being implemented
};

