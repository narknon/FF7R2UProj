#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "EndNewCardDeckWindow.generated.h"

class UWidget;

UCLASS(Blueprintable)
class UEndNewCardDeckWindow : public UObject {
    GENERATED_BODY()
public:
    UEndNewCardDeckWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnPresetDeckListSetupItem(UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnPresetDeckListSelectedIndexChanged(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnPresetDeckListMeasureItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnOriginDeckSetupItem(UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnOriginDeckSelectedIndexChanged(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnOriginDeckPressedItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnOriginDeckMeasureItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnOriginDeckDeckListSetupItem(UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnOriginDeckDeckListMeasureItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListBoxSortSelectedIndexChanged(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListBoxSort02PressedItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListBoxSort01PressedItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListBoxFilterSelectedIndexChanged(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListBoxFilter07PressedItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListBoxFilter06PressedItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListBoxFilter05PressedItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListBoxFilter04PressedItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListBoxFilter03PressedItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListBoxFilter02PressedItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListBoxFilter01PressedItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEditingDeckSelectedIndexChanged(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnDeckScrollListSetupItem(UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnDeckScrollListSelectedIndexChanged(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnDeckScrollListPressedItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnDeckListSetupItem(UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnDeckListMeasureItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCopyDeckBtn02Clicked();
    
    UFUNCTION(BlueprintCallable)
    void OnCopyDeckBtn01Clicked();
    
    UFUNCTION(BlueprintCallable)
    void OnCardListPlayerRowSetupItem(UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCardListPlayerRowSelectedIndexChanged(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnCardListPlayerRowMeasureItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCardListPlayerCellSetupItem(int32 InRowIndex, UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCardListPlayerCellSelectedIndexChanged(int32 InRowIndex, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCardListEditRowSetupItem(UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCardListEditRowSelectedIndexChanged(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnCardListEditRowMeasureItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCardListEditCellSetupItem(int32 InRowIndex, UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCardListEditCellSelectedIndexChanged(int32 InRowIndex, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCardListEditCellPressedItem(int32 InRowIndex, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCardListAllRowSetupItem(UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCardListAllRowSelectedIndexChanged(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnCardListAllRowMeasureItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCardListAllCellSetupItem(int32 InRowIndex, UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCardListAllCellSelectedIndexChanged(int32 InRowIndex, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCardDeckListSetupItem(UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCardDeckListSelectedIndexChanged(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCardDeckListPressedItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnCardDeckListMeasureItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBtn02Clicked();
    
    UFUNCTION(BlueprintCallable)
    void OnBtn01Clicked();
    
};

