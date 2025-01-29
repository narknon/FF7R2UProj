#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "EndBTDecorator_SetVisibility.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_SetVisibility : public UBTDecorator {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Visibility;
    
    UEndBTDecorator_SetVisibility();

};

