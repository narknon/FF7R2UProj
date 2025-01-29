#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndNewSenseTitleCell.generated.h"

class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndNewSenseTitleCell : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Title;
    
    UEndNewSenseTitleCell();

};

