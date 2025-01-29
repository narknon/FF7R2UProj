#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndEquipRemoveBtn.generated.h"

class UEndCanvasPanel;

UCLASS(Blueprintable, EditInlineNew)
class UEndEquipRemoveBtn : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* BtnRemove;
    
    UEndEquipRemoveBtn();

};

