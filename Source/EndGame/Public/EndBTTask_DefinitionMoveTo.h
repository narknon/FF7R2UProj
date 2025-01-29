#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveApproachType.h"
#include "EndBTTask_MoveTo.h"
#include "EndBTTask_DefinitionMoveTo.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_DefinitionMoveTo : public UEndBTTask_MoveTo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIMoveApproachType MoveApproach;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableOverridePathFindInterval;
    
    UEndBTTask_DefinitionMoveTo();

};

