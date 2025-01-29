#pragma once
#include "CoreMinimal.h"
#include "SummonWarpPointMoveOnlyBattle.generated.h"

USTRUCT(BlueprintType)
struct FSummonWarpPointMoveOnlyBattle {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName battleSceneID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Phase;
    
    ENDGAME_API FSummonWarpPointMoveOnlyBattle();
};

