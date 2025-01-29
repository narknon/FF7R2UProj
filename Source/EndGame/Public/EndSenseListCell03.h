#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndSenseListCell03.generated.h"

class UEndImage;
class UEndListBox;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndSenseListCell03 : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImage* Img_Base;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Item;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndListBox* List_Icon_Status_00;
    
    UEndSenseListCell03();

};

