#pragma once
#include "CoreMinimal.h"
#include "EndMapJournalMenuWindow.h"
#include "EndWorldReportMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndWorldReportMenu : public UEndMapJournalMenuWindow {
    GENERATED_BODY()
public:
    UEndWorldReportMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnReportListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnReportListSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnReportListCleanupItem(UWidget* ItemWidget);
    
    UFUNCTION(BlueprintCallable)
    void OnReportAreaChangeBtnSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListTerm3SetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListTerm2SetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEndVirtualScrollBox224SetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
};

