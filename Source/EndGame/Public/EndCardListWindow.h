#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCardListWindow.generated.h"

class UEndBillboard;
class UEndCanvasPanel;
class UEndCardGameCardPane;
class UEndTextBlock;
class UEndVirtualScrollBox;

UCLASS(Blueprintable, EditInlineNew)
class UEndCardListWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Pnl_EnemyName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_EnemyName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBillboard* Billboard_DeckThumbnail;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* End_Text;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* Virtual_Scroll_Box_Card;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Total;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_TotalNumber;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCardGameCardPane* Card_Small;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Reward_00;
    
    UEndCardListWindow();

};

