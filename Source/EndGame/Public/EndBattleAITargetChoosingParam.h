#pragma once
#include "CoreMinimal.h"
#include "ETargetChoosingSort.h"
#include "ETargetChoosingTag.h"
#include "EndBattleAITargetChoosingParam.generated.h"

class AEndCharacter;

USTRUCT(BlueprintType)
struct FEndBattleAITargetChoosingParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<AEndCharacter*> AssignedTargets;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<ETargetChoosingTag> PriorityTagList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ETargetChoosingSort SortMethod;
    
    ENDGAME_API FEndBattleAITargetChoosingParam();
};

