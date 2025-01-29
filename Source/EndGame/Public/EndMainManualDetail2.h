#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMainManualDetail2.generated.h"

class UEndBillboard;
class UEndCanvasPanel;
class UEndStringScrollBox;

UCLASS(Blueprintable, EditInlineNew)
class UEndMainManualDetail2 : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Nut_Movie;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBillboard* Img_Movie;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndStringScrollBox* Txt_Box;
    
    UEndMainManualDetail2();

};

