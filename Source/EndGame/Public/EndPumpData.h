#pragma once
#include "CoreMinimal.h"
#include "EndStreamableAssets.h"
#include "EndPumpData.generated.h"

USTRUCT(BlueprintType)
struct FEndPumpData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndStreamableAssets> StreamableAssets;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FString> AssetPaths;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FString> MassiveEnvironmentAssetPaths;
    
    ENDGAME_API FEndPumpData();
};

