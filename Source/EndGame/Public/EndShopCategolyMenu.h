#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndShopCategolyMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndShopCategolyMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndShopCategolyMenu();

    UFUNCTION(BlueprintCallable)
    void OnShopCategolyCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnPressedItem(int32 ItemIndex);
    
};

