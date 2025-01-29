#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndGambitEditMenuWidget.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndGambitEditMenuWidget : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndGambitEditMenuWidget();

    UFUNCTION(BlueprintCallable)
    void OnPresetListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnPresetListBSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnIconListSetupItem4(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnIconListSetupItem3(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnIconListSetupItem2(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnIconListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnConfirmSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnConfirmPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnConditionListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnConditionListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnConditionListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnActionNeedListSetupItem2(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnActionNeedListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnActionListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnActionListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnActionListPressedItem(int32 CellIndex);
    
};

