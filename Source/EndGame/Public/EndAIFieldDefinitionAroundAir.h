#pragma once
#include "CoreMinimal.h"
#include "EndAIFieldDefinitionWanderingAir.h"
#include "EndAIFieldDefinitionAroundAir.generated.h"

UCLASS(Blueprintable)
class UEndAIFieldDefinitionAroundAir : public UEndAIFieldDefinitionWanderingAir {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AroundDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AroundDistanceWidth;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AroundTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AroundTimeWidth;
    
    UEndAIFieldDefinitionAroundAir();

};

