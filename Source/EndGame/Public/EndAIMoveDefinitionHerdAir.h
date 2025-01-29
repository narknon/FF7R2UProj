#pragma once
#include "CoreMinimal.h"
#include "EndAIMoveDefinitionHerd.h"
#include "EndAIMoveDefinitionHerdAir.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinitionHerdAir : public UEndAIMoveDefinitionHerd {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float HeightWidth;
    
    UEndAIMoveDefinitionHerdAir();

};

