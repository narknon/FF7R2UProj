#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMainMateriaChangeSelectWindow.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMainMateriaChangeSelectWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndMainMateriaChangeSelectWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnEndEquipChangeWeaponCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEndEquipChangeMateriaCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEndEquipChangeEquipCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
};

