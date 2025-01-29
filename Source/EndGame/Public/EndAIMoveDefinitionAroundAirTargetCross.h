#pragma once
#include "CoreMinimal.h"
#include "EndAIMoveDefinitionAroundAir.h"
#include "EndAIMoveDefinitionAroundAirTargetCross.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinitionAroundAirTargetCross : public UEndAIMoveDefinitionAroundAir {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AroundTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AroundTimeWidth;
    
    UEndAIMoveDefinitionAroundAirTargetCross();

};

