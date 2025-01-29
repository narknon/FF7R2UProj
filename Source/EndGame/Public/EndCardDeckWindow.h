#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndMainMenuWindow.h"
#include "EndCardDeckWindow.generated.h"

class UEndBillboard;
class UEndCanvasPanel;
class UEndCardEditWindow;
class UEndCardInformationWindow;
class UEndCardListWindow;
class UEndCardViewWindow;
class UEndUserWidget;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndCardDeckWindow : public UEndMainMenuWindow {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Pnl_Menu_Card;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Pnl_Bg;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBillboard* Billboard_Bg;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndUserWidget* DeckList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCardListWindow* CardList_Player;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCardListWindow* EnemyInformation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCardViewWindow* Card_View;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCardEditWindow* Card_EditList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCardInformationWindow* GameInformation;
    
    UEndCardDeckWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnCradDeckListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCradDeckListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCradDeckListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnCradDeckListMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCradDeckEditSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCradDeckEditSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCradDeckEditPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnCradDeckEditMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCradDeckEditContentsSetupItem(int32 VerticalIndex, UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCradDeckEditContentsSelectedIndexChanged(int32 VerticalIndex, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCradDeckEditContentsPressedItem(int32 VerticalIndex, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCradDeckContentsSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCradDeckContentsPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnCradDeckContentsMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCradDeckContentsListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
};

