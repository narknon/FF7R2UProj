#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EEndStreamingVolumeTargetType.h"
#include "EndStreamingGirdData.h"
#include "EndStreamingGrid.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndStreamingGrid : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float GridSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BaseLoadDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BaseUnloadMargin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool ForCollisionStreaming;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool ForCollisionStreamingToCollisionAsset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCheckedHeightCollisionStream;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ThresholdCheckedHeightCollisionStream;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool NoWaitCollisionStreaming;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndStreamingVolumeTargetType StreamingTarget;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndStreamingGirdData> StreamingLevels;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bDisabled: 1;
    
    AEndStreamingGrid(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void PauseStreamingGrid(bool bEnable);
    
    UFUNCTION(BlueprintCallable)
    void EnableStreamingGrid(bool bEnable);
    
};

