#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndUserWidget.h"
#include "EndCardChallengeDeckWindow.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndCardChallengeDeckWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndCardChallengeDeckWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnVirtualScrollBoxCard1SetupItem(UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnVirtualScrollBoxCard1SelectedIndexChanged(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnVirtualScrollBoxCard1MeasureItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnVirtualScrollBoxCard1CellSetupItem(int32 InRowIndex, UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnVirtualScrollBoxCard1CellSelectedIndexChanged(int32 InRowIndex, int32 InItemIndex);
    
};

