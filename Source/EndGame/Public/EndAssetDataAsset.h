#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EndAssetClass.h"
#include "EndAssetData.h"
#include "EndAssetDataSoft.h"
#include "EndAssetDataAsset.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndAssetDataAsset : public UDataAsset {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAssetData> AssetDataList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAssetDataSoft> AssetDataSoftList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAssetClass> AssetClassList;
    
public:
    UEndAssetDataAsset();

};

