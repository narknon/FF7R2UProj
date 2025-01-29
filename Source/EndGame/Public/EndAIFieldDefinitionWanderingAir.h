#pragma once
#include "CoreMinimal.h"
#include "EndAIFieldDefinitionWandering.h"
#include "EndAIFieldDefinitionWanderingAir.generated.h"

UCLASS(Blueprintable)
class UEndAIFieldDefinitionWanderingAir : public UEndAIFieldDefinitionWandering {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FlyingHeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FlyingHeightWidth;
    
    UEndAIFieldDefinitionWanderingAir();

};

