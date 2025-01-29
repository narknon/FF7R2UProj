#pragma once
#include "CoreMinimal.h"
#include "EndAIMoveDefinitionAround.h"
#include "EndAIMoveDefinitionAroundAir.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinitionAroundAir : public UEndAIMoveDefinitionAround {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseActonDefinitionHeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float HeightMed;
    
    UEndAIMoveDefinitionAroundAir();

};

