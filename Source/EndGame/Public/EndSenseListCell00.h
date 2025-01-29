#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndSenseListCell00.generated.h"

class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndSenseListCell00 : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Item;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Num;
    
    UEndSenseListCell00();

};

