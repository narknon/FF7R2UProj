#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCategorySwitch2Cell.generated.h"

class UEndCanvasPanel;
class UEndIconItem;
class UEndImage;

UCLASS(Blueprintable, EditInlineNew)
class UEndCategorySwitch2Cell : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* TitleBase;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndIconItem* Icon_Item;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImage* Icon_New_Item;
    
    UEndCategorySwitch2Cell();

};

