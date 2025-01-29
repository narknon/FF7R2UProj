#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndAutoSettingCell.generated.h"

class UEndCanvasPanel;
class UEndIconItem;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndAutoSettingCell : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* All_EquipSelect_Cell;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Title;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndIconItem* Icon_Item;
    
    UEndAutoSettingCell();

};

