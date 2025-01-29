#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndEquipInfoDetailCore2.generated.h"

class UEndCanvasPanel;
class UEndVirtualScrollBox;

UCLASS(Blueprintable, EditInlineNew)
class UEndEquipInfoDetailCore2 : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* CoreInfoBox;
    
    UEndEquipInfoDetailCore2();

};

