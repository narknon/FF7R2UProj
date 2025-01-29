#pragma once
#include "CoreMinimal.h"
#include "EActorMoveMode.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CheckActorMoveMode.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CheckActorMoveMode : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EActorMoveMode actorMoveMode;
    
    UEndBTDecorator_CheckActorMoveMode();

};

