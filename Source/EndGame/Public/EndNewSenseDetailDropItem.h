#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndNewSenseDetailDropItem.generated.h"

class UEndListBox;
class UEndNewSenseTitleCell;

UCLASS(Blueprintable, EditInlineNew)
class UEndNewSenseDetailDropItem : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNewSenseTitleCell* Title_RareDropItems;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndListBox* List_RareDropItems;
    
    UEndNewSenseDetailDropItem();

};

