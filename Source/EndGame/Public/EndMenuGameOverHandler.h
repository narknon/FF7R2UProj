#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndMenuGameOverHandler.generated.h"

class UWidget;

UCLASS(Blueprintable)
class UEndMenuGameOverHandler : public UObject {
    GENERATED_BODY()
public:
    UEndMenuGameOverHandler();

    UFUNCTION(BlueprintCallable)
    void OnCommandClicked(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
};

