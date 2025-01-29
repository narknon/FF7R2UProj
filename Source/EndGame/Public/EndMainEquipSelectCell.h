#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMainEquipSelectCell.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndMainEquipSelectCell : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndMainEquipSelectCell();

private:
    UFUNCTION(BlueprintCallable)
    void OnEndEquipCellClicked();
    
};

