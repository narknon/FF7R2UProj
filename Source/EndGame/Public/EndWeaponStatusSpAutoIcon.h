#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndWeaponStatusSpAutoIcon.generated.h"

class UEndCanvasPanel;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndWeaponStatusSpAutoIcon : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Auto;
    
    UEndWeaponStatusSpAutoIcon();

};

