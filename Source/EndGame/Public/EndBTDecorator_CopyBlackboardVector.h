#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_CopyBlackboardVector.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CopyBlackboardVector : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector TargetBlackboardKey;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBlackboardKeySelector SourceBlackboardKey;
    
    UEndBTDecorator_CopyBlackboardVector();

};

