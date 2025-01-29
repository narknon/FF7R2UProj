#pragma once
#include "CoreMinimal.h"
#include "EndMassiveEnvironmentComponent.h"
#include "EndStreamableAssetData.h"
#include "EndStreamableAssets.generated.h"

USTRUCT(BlueprintType)
struct FEndStreamableAssets {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ViewTarget;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 CutIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Timestamp;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint64 FrameCounter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndStreamableAssetData> StreamableAssetData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndMassiveEnvironmentComponent> StreamableMEComponents;
    
    ENDGAME_API FEndStreamableAssets();
};

