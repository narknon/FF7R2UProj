#pragma once
#include "CoreMinimal.h"
#include "EndAILevelActorInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndAILevelActorInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LevelName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ActorName;
    
    ENDGAME_API FEndAILevelActorInfo();
};

