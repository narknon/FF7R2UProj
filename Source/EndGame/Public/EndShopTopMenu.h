#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndShopTopMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndShopTopMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndShopTopMenu();

    UFUNCTION(BlueprintCallable)
    void OnShopTopCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnPressedItem(int32 ItemIndex);
    
};

