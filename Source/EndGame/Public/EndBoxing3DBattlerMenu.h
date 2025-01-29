#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndBoxing3DBattlerMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndBoxing3DBattlerMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndBoxing3DBattlerMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnUnitListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnUnitListSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnUnitListPressedItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnPrizeListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnPrizeList2SetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
};

