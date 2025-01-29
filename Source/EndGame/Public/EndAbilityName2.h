#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndAbilityName2.generated.h"

class UEndCanvasPanel;
class UEndImage;
class UEndProgressBar;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndAbilityName2 : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* AbilityBox;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_AccessoryInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndProgressBar* Gauge_Exp;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImage* Icon_Clear;
    
    UEndAbilityName2();

};

