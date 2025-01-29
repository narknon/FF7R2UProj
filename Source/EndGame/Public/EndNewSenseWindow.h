#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndNewSenseWindow.generated.h"

class UEndCanvasPanel;
class UEndNewSenseDetailWindow;

UCLASS(Blueprintable, EditInlineNew)
class UEndNewSenseWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNewSenseDetailWindow* NewSenseDetail;
    
    UEndNewSenseWindow();

};

