#pragma once
#include "CoreMinimal.h"
#include "EndMainMenuWindow.h"
#include "EndMainEquipMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMainEquipMenu : public UEndMainMenuWindow {
    GENERATED_BODY()
public:
    UEndMainEquipMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnEndEquipMenuMemberClicked();
    
    UFUNCTION(BlueprintCallable)
    void OnCommandMemberCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandEquipStatusCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandEquipCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
};

