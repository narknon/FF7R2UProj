#pragma once
#include "CoreMinimal.h"
#include "EndBuggySpawnPointData.generated.h"

USTRUCT(BlueprintType)
struct FEndBuggySpawnPointData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName PlayerSpawnPointName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BuggySpawnPointName;
    
    ENDGAME_API FEndBuggySpawnPointData();
};

