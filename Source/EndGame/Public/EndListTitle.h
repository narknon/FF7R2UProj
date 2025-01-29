#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndListTitle.generated.h"

class UEndBillboard;
class UEndImage;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndListTitle : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBillboard* Billboard_Deck_Thumbnail;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Title;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImage* Img_Mark;
    
    UEndListTitle();

};

