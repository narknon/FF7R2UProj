#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndPlayerLevelGauge.generated.h"

class UEndCanvasPanel;
class UEndCircle;
class UEndPieImage;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndPlayerLevelGauge : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndPieImage* Gauge_TotalPie;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCircle* Gauge_Total;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Level_Num;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Exp_Num;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Exp_Total;
    
    UEndPlayerLevelGauge();

};

