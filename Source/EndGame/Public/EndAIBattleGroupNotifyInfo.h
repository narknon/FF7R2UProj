#pragma once
#include "CoreMinimal.h"
#include "EndAIBattleGroupNotifyInfo.generated.h"

class AEndCharacter;

USTRUCT(BlueprintType)
struct FEndAIBattleGroupNotifyInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Message;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName GroupId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bFromLeader;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AEndCharacter* SendCharacter;
    
    ENDGAME_API FEndAIBattleGroupNotifyInfo();
};

