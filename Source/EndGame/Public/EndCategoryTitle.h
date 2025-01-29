#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCategoryTitle.generated.h"

class UEndIconCategory;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndCategoryTitle : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndIconCategory* Icon_Category;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_MainTitle;
    
    UEndCategoryTitle();

};

