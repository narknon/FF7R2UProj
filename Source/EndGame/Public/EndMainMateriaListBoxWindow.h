#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMainMateriaListBoxWindow.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMainMateriaListBoxWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndMainMateriaListBoxWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnSetupItemForShop(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMateriaCellSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMateriaCellPressed(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandMateriaCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
};

