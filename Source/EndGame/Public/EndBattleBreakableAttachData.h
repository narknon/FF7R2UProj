#pragma once
#include "CoreMinimal.h"
#include "EndBattleBreakableAttachData.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBattleBreakableAttachData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SocketName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ActorName;
    
    FEndBattleBreakableAttachData();
};

