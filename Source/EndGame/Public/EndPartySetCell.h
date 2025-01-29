#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndPartySetCell.generated.h"

class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndPartySetCell : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Num;
    
    UEndPartySetCell();

};

