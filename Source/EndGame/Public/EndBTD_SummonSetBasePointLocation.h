#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "EndBTD_SummonSetBasePointLocation.generated.h"

UCLASS(Blueprintable)
class UEndBTD_SummonSetBasePointLocation : public UBTDecorator {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BlackBoardName_WarpLocation;
    
    UEndBTD_SummonSetBasePointLocation();

};

