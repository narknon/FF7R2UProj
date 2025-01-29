#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndItemCraftPopupWindow.generated.h"

class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndItemCraftPopupWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Title;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_GetRecipe;
    
    UEndItemCraftPopupWindow();

};

