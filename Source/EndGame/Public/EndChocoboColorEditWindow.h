#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndChocoboColorEditWindow.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndChocoboColorEditWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndChocoboColorEditWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnTabMenuSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
};

