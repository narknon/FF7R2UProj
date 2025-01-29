#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMateriaSelectTab.generated.h"

class UEndCanvasPanel;
class UEndVirtualScrollBox;

UCLASS(Blueprintable, EditInlineNew)
class UEndMateriaSelectTab : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* TabList;
    
    UEndMateriaSelectTab();

};

