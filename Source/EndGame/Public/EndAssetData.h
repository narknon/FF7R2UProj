#pragma once
#include "CoreMinimal.h"
#include "EndAssetData.generated.h"

class UObject;

USTRUCT(BlueprintType)
struct ENDGAME_API FEndAssetData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AssetName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UObject*> AssetUserData;
    
    FEndAssetData();
};

