#pragma once
#include "CoreMinimal.h"
#include "EndAIMoveDefinitionConfrontOnly.h"
#include "EndAIMoveDefinitionConfrontAirOnly.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinitionConfrontAirOnly : public UEndAIMoveDefinitionConfrontOnly {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float HeightMed;
    
    UEndAIMoveDefinitionConfrontAirOnly();

};

