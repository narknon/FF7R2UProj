#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndResearchTargetWindow.generated.h"

class UEndCanvasPanel;
class UEndResearchTargetList;
class UEndTextBlock;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndResearchTargetWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_ReportTitle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndResearchTargetList* List_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndResearchTargetList* List_1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndResearchTargetList* List_2;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndResearchTargetList* List_3;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndResearchTargetList* List_4;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndResearchTargetList* List_5;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndResearchTargetList* List_6;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Btn;
    
    UEndResearchTargetWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnListSetupItem(int32 Category, UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListSelectedIndexChanged(int32 Category, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListPressedItem(int32 Category, int32 CellIndex);
    
};

