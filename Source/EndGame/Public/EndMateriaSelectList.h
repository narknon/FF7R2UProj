#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMateriaSelectList.generated.h"

class UEndCanvasPanel;
class UEndMateriaSelectTab;
class UEndTextBlock;
class UEndVirtualScrollBox;

UCLASS(Blueprintable, EditInlineNew)
class UEndMateriaSelectList : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* SelectList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Title_1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_TitleValue;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMateriaSelectTab* Tab;
    
    UEndMateriaSelectList();

};

