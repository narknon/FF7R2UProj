#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCardEditWindow.generated.h"

class UEndCanvasPanel;
class UEndTextBlock;
class UEndVirtualScrollBox;

UCLASS(Blueprintable, EditInlineNew)
class UEndCardEditWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* Virtual_Scroll_Box_Edit;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Description;
    
    UEndCardEditWindow();

};

