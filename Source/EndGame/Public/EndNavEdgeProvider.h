#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AI/Navigation/NavEdgeProviderInterface.h"
#include "EndNavEdgeProvider.generated.h"

UCLASS(Blueprintable)
class UEndNavEdgeProvider : public UObject, public INavEdgeProviderInterface {
    GENERATED_BODY()
public:
    UEndNavEdgeProvider();


    // Fix for true pure virtual functions not being implemented
};

