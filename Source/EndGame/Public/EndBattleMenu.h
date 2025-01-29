#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndBattleMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndBattleMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndBattleMenu();

    UFUNCTION(BlueprintCallable)
    void OnPressedItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
};

