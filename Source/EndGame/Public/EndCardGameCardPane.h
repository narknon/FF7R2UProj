#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCardGameCardPane.generated.h"

class UEndCanvasPanel;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndCardGameCardPane : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Pnl_Limit;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Limit;
    
    UEndCardGameCardPane();

};

