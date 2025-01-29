#pragma once
#include "CoreMinimal.h"
#include "EndSkeletalMeshActor.h"
#include "EndWorldReportActor.generated.h"

class UEndSyncPoseSkeletalMeshComponent;
class USQEXSEADSound;

UCLASS(Blueprintable)
class ENDGAME_API AEndWorldReportActor : public AEndSkeletalMeshActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 DisplayMaterialIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float CoordinateAnimationDuration;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSyncPoseSkeletalMeshComponent* DisplayMeshComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSyncPoseSkeletalMeshComponent* MovieMeshComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEXSEADSound* Monitor_Change_SE;
    
public:
    AEndWorldReportActor(const FObjectInitializer& ObjectInitializer);

private:
    UFUNCTION(BlueprintCallable)
    void OnMediaOpened(const FString& OpenedUrl);
    
    UFUNCTION(BlueprintCallable)
    void OnMediaEndReached();
    
};

