#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndWeaponUpgradeCoreListBoxWindow.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndWeaponUpgradeCoreListBoxWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndWeaponUpgradeCoreListBoxWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnCellSetup(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCellSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCellPressed(int32 CellIndex);
    
};

