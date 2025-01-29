#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndStatusAbilityList.generated.h"

class UEndCanvasPanel;
class UEndVirtualScrollBox;

UCLASS(Blueprintable, EditInlineNew)
class UEndStatusAbilityList : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* AbilityList;
    
    UEndStatusAbilityList();

};

