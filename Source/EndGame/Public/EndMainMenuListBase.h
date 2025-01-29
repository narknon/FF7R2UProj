#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMainMenuListBase.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndMainMenuListBase : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndMainMenuListBase();

protected:
    UFUNCTION(BlueprintCallable)
    void OnCellPressed(int32 CellIndex);
    
};

