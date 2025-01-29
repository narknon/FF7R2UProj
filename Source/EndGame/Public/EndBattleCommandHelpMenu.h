#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndBattleCommandHelpMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndBattleCommandHelpMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndBattleCommandHelpMenu();

    UFUNCTION(BlueprintCallable)
    void OnCommandShortcutHelpListCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandHelpListCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
};

