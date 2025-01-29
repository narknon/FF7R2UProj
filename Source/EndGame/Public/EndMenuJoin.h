#pragma once
#include "CoreMinimal.h"
#include "EPlayerType.h"
#include "EEndMenuJoinMode.h"
#include "EndMenuJoin.generated.h"

USTRUCT(BlueprintType)
struct FEndMenuJoin {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EPlayerType member;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndMenuJoinMode Mode;
    
    ENDGAME_API FEndMenuJoin();
};

