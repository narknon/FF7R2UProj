#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMagicSelectList.generated.h"

class UEndCanvasPanel;
class UEndTextBlock;
class UEndVirtualScrollBox;

UCLASS(Blueprintable, EditInlineNew)
class UEndMagicSelectList : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* All_SelectList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Title;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_TitleValue;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* SelectList;
    
    UEndMagicSelectList();

};

