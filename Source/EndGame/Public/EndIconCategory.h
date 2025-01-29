#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndIconCategory.generated.h"

class UEndIconItem;

UCLASS(Blueprintable, EditInlineNew)
class UEndIconCategory : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndIconItem* Icon_Item;
    
    UEndIconCategory();

};

