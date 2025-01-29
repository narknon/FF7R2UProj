#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndMenuFieldMenuHandler.generated.h"

UCLASS(Blueprintable)
class UEndMenuFieldMenuHandler : public UObject {
    GENERATED_BODY()
public:
    UEndMenuFieldMenuHandler();

    UFUNCTION(BlueprintCallable)
    void OnCommandClicked();
    
};

