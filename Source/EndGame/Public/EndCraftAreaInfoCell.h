#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCraftAreaInfoCell.generated.h"

class UEndCanvasPanel;
class UEndImage;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndCraftAreaInfoCell : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Area;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImage* Icon_Advantage;
    
    UEndCraftAreaInfoCell();

};

