#pragma once
#include "CoreMinimal.h"
#include "EndPopupMessageColors.h"
#include "EndUserWidget.h"
#include "EndDamageSubText.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndDamageSubText : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndPopupMessageColors NormalColors;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndPopupMessageColors ExtraBonusColors;
    
    UEndDamageSubText();

};

