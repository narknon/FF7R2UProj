#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndEquipCategoryCell.generated.h"

class UEndIconItem;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndEquipCategoryCell : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_EquipCategory;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_NotUsed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndIconItem* Icon_Item;
    
    UEndEquipCategoryCell();

};

