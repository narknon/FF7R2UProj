#pragma once
#include "CoreMinimal.h"
#include "EEndAIBattleGroupLeader.h"
#include "Templates/SubclassOf.h"
#include "EndAIBattleGroupSetting.generated.h"

class UEndAIMoveDefinitionHerd;

USTRUCT(BlueprintType)
struct FEndAIBattleGroupSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName GroupId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIBattleGroupLeader LeaderType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseMoveDefinitionHerd;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIMoveDefinitionHerd> MoveDefinitionHerdClass;
    
    ENDGAME_API FEndAIBattleGroupSetting();
};

