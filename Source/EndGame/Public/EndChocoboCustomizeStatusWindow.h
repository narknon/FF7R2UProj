#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndChocoboCustomizeStatusWindow.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndChocoboCustomizeStatusWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndChocoboCustomizeStatusWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnStatusListSetupItem(UWidget* ItemWidget, int32 InItemIndex);
    
};

