#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCraftAreaInfoWindow.generated.h"

class UEndCanvasPanel;
class UEndCraftAreaInfo;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndCraftAreaInfoWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCraftAreaInfo* AreaInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Pnl_Title;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Title;
    
    UEndCraftAreaInfoWindow();

};

