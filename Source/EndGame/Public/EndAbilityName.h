#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndAbilityName.generated.h"

class UEndAbilityName2;
class UEndCanvasPanel;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndAbilityName : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* AbilityBox;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_AbilityTitle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndAbilityName2* AbilityName2;
    
    UEndAbilityName();

};

