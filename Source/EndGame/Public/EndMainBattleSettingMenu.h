#pragma once
#include "CoreMinimal.h"
#include "EndMainMenuWindow.h"
#include "EndMainBattleSettingMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMainBattleSettingMenu : public UEndMainMenuWindow {
    GENERATED_BODY()
public:
    UEndMainBattleSettingMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnSettingCellSetup(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSettingCellSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSettingCellPressed(int32 SettingCellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLimitCellSetup(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLimitCellSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLimitCellPressed(int32 LimitCellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnControlTypeSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnControlTypeCellSetup(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnControlTypeCellPressed(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCategorySelectedIndexChanged(int32 CategoryCellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCategoryCellSetup(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCategoryCellPressed(int32 CommandCellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnAbilitySelectedIndexChanged(int32 AbilityCellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnAbilityCellSetup(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnAbilityCellPressed(int32 AbilityCellIndex);
    
};

