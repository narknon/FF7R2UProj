#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveApproachType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsStrafeMoveDefinition.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsStrafeMoveDefinition : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndAIMoveApproachType> MoveApproachTypes;
    
    UEndBTDecorator_IsStrafeMoveDefinition();

};

