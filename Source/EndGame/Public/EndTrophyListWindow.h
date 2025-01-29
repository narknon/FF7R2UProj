#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndTrophyListWindow.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndTrophyListWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndTrophyListWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnTrophyListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnTrophyListSelectedIndexChanged(int32 ItemIndex);
    
};

