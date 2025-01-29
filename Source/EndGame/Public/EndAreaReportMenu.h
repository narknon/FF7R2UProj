#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndAreaReportMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndAreaReportMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndAreaReportMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnAreaReportListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnAreaReportListSelectedIndexChanged(int32 ItemIndex);
    
};

