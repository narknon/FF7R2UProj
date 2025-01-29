#pragma once
#include "CoreMinimal.h"
#include "EndNaviMapVolumePoly.h"
#include "EndSceneNaviMapVolumeLodInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndSceneNaviMapVolumeLodInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndNaviMapVolumePoly> VolumePolysWithWorldOffset;
    
    ENDGAME_API FEndSceneNaviMapVolumeLodInfo();
};

