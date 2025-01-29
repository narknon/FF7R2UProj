#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndAIDangerSourceInterface.h"
#include "EndAIDangerSource.generated.h"

UCLASS(Blueprintable)
class UEndAIDangerSource : public UObject, public IEndAIDangerSourceInterface {
    GENERATED_BODY()
public:
    UEndAIDangerSource();


    // Fix for true pure virtual functions not being implemented
};

