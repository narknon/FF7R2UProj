#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EndPlayBlendSpaceActionActorInterface.generated.h"

UINTERFACE(Blueprintable)
class UEndPlayBlendSpaceActionActorInterface : public UInterface {
    GENERATED_BODY()
};

class IEndPlayBlendSpaceActionActorInterface : public IInterface {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    float OnGetCurrentBlendSpaceInput();
    
};

