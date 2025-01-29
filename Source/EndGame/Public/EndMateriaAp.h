#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMateriaAp.generated.h"

class UEndCanvasPanel;
class UEndProgressBar;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndMateriaAp : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_ApInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndProgressBar* Gauge_Ap;
    
    UEndMateriaAp();

};

