#pragma once
#include "CoreMinimal.h"
#include "WallManageParam.generated.h"

USTRUCT(BlueprintType)
struct FWallManageParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 WallID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 GroupId;
    
    ENDGAME_API FWallManageParam();
};

