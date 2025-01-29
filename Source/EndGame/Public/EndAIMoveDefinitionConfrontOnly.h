#pragma once
#include "CoreMinimal.h"
#include "EndAIMoveDefinitionConfrontBase.h"
#include "EndAIMoveDefinitionConfrontOnly.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinitionConfrontOnly : public UEndAIMoveDefinitionConfrontBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TimeOut;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DistanceMin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DistanceMed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DistanceMax;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DistanceMedWidth;
    
    UEndAIMoveDefinitionConfrontOnly();

};

