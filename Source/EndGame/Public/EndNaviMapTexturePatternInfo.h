#pragma once
#include "CoreMinimal.h"
#include "EndNaviMapTexturePatternInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndNaviMapTexturePatternInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName PatternName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName NavMeshDirName;
    
    ENDGAME_API FEndNaviMapTexturePatternInfo();
};

