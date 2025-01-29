#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/AssetUserData.h"
#include "EndEnvironmentWaterVolumeAssetUserData_Curve.h"
#include "EndEnvironmentWaterVolumeAssetUserData_Speed.h"
#include "EndEnvironmentWaterVolumeAssetUserData.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndEnvironmentWaterVolumeAssetUserData : public UAssetUserData {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseLocalSpace;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector Location;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndEnvironmentWaterVolumeAssetUserData_Curve> Curves;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndEnvironmentWaterVolumeAssetUserData_Speed> Speeds;
    
    UEndEnvironmentWaterVolumeAssetUserData();

};

