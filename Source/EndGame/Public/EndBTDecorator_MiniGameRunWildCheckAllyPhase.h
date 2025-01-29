#pragma once
#include "CoreMinimal.h"
#include "EEndAnimalRunAIPhase.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_MiniGameRunWildCheckAllyPhase.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_MiniGameRunWildCheckAllyPhase : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName RoleName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimalRunAIPhase Phase;
    
    UEndBTDecorator_MiniGameRunWildCheckAllyPhase();

};

