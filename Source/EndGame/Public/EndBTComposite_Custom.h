#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "EEndCustomCompositeReturnCondition.h"
#include "EndBTComposite_Custom.generated.h"

UCLASS(Blueprintable)
class UEndBTComposite_Custom : public UBTCompositeNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndCustomCompositeReturnCondition ReturnCondition;
    
    UEndBTComposite_Custom();

};

