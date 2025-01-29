#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndAutoSettingList.generated.h"

class UEndCanvasPanel;
class UEndTextBlock;
class UEndVirtualScrollBox;

UCLASS(Blueprintable, EditInlineNew)
class UEndAutoSettingList : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* All_SortList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* SelectList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Info;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Title_1;
    
    UEndAutoSettingList();

};

