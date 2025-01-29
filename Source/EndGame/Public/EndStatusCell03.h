#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndStatusCell03.generated.h"

class UEndBillboard;
class UEndCanvasPanel;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndStatusCell03 : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Pnl_StatusCell;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBillboard* Img_Player;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Description_Title;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Description_Info;
    
    UEndStatusCell03();

};

