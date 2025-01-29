#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCoreListCell.generated.h"

class UEndCanvasPanel;
class UEndIconItem;
class UEndImage;

UCLASS(Blueprintable, EditInlineNew)
class UEndCoreListCell : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* All_Pnl_Core_Cell;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndIconItem* Icon_Item;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImage* Cursor_Selected;
    
    UEndCoreListCell();

};

