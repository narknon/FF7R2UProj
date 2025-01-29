#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndItemCategoryList.generated.h"

class UEndCanvasPanel;
class UEndVirtualScrollBox;

UCLASS(Blueprintable, EditInlineNew)
class UEndItemCategoryList : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* All_LeftMenu;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* ItemCategoryList;
    
    UEndItemCategoryList();

};

