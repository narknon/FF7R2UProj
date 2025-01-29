#pragma once
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "EndAIMoveDefinitionConfrontTwoStageToActionInfo.generated.h"

class UEndAIMoveDefinition;

USTRUCT(BlueprintType)
struct FEndAIMoveDefinitionConfrontTwoStageToActionInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DistanceMin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DistanceMax;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LotProbability;
    
    ENDGAME_API FEndAIMoveDefinitionConfrontTwoStageToActionInfo();
};

