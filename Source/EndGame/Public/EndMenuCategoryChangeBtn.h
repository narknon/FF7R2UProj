#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMenuCategoryChangeBtn.generated.h"

class UEndVirtualScrollBox;

UCLASS(Blueprintable, EditInlineNew)
class UEndMenuCategoryChangeBtn : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* StoneBox;
    
    UEndMenuCategoryChangeBtn();

};

