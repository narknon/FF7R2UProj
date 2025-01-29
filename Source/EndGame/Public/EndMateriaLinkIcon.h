#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMateriaLinkIcon.generated.h"

class UEndCanvasPanel;
class UEndIconItem;

UCLASS(Blueprintable, EditInlineNew)
class UEndMateriaLinkIcon : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_63;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndIconItem* Icon_Item;
    
    UEndMateriaLinkIcon();

};

