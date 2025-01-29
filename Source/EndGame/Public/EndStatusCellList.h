#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndStatusCellList.generated.h"

class UEndCanvasPanel;
class UEndStatusCellTitle2;
class UEndVirtualScrollBox;

UCLASS(Blueprintable, EditInlineNew)
class UEndStatusCellList : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* All_StatusCell_List;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* DescriptionList2;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndStatusCellTitle2* Title;
    
    UEndStatusCellList();

};

