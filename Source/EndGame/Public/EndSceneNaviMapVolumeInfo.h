#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EEndNaviMapLayer.h"
#include "EEndNaviMapOpenGroup.h"
#include "EEndNaviMapVisitGroup.h"
#include "EndSceneNaviMapVolumeLodInfo.h"
#include "EndSceneNaviMapVolumeInfo.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndSceneNaviMapVolumeInfo {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndNaviMapLayer LayerNumber;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndNaviMapOpenGroup OpenGroupNumber;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndNaviMapVisitGroup VisitGroupNumber;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 UniqueIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName VolumeName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBox VolumeBoundsWithWorldOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndSceneNaviMapVolumeLodInfo> VolumeLods;
    
    FEndSceneNaviMapVolumeInfo();
};

