#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndSenseListCell01.generated.h"

class UEndListBox;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndSenseListCell01 : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndListBox* List_Icon_Status_00;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndListBox* List_Icon_Status_01;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Item;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Question;
    
    UEndSenseListCell01();

};

