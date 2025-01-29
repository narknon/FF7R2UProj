#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCardUnitList.generated.h"

class UEndCanvasPanel;
class UEndVirtualScrollBox;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndCardUnitList : public UEndUserWidget {
    GENERATED_BODY()
public:
    DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnCardUnitListSetupItem, int32, VerticalIndex, UWidget*, ItemWidget, int32, ItemIndex);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCardUnitListSelectedIndexChanged, int32, VerticalIndex, int32, ItemIndex);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCardUnitListPressedItem, int32, VerticalIndex, int32, ItemIndex);
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* EndVirtualScrollBox_103;
    
    UEndCardUnitList();

private:
    UFUNCTION(BlueprintCallable)
    void OnSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnPressedItem(int32 CellIndex);
    
};

