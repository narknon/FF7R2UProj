#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndNaviMapVolumePoly.h"
#include "EndSceneNaviMapRegionVolumeInfo.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndSceneNaviMapRegionVolumeInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LocationId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName NaviMapId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName RegionName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName VolumeName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBox VolumeBoundsWithWorldOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndNaviMapVolumePoly> VolumePolysWithWorldOffset;
    
    FEndSceneNaviMapRegionVolumeInfo();
};

