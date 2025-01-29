#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCardDeckNpcWindow.generated.h"

class UEndCanvasPanel;
class UEndCardDeckWindow;

UCLASS(Blueprintable, EditInlineNew)
class UEndCardDeckNpcWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCardDeckWindow* MainMenu_Card_Top;
    
    UEndCardDeckNpcWindow();

};

