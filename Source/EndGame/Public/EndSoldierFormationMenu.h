#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndUserWidget.h"
#include "EndSoldierFormationMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndSoldierFormationMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndSoldierFormationMenu();

private:
    UFUNCTION(BlueprintCallable)
    FVector2D OnReserveListMeasureItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnReserveListItemSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnEditListMeasureItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEditListItemSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
};

