#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndUserWidget.h"
#include "EndCondorFortATBGauge.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndCondorFortATBGauge : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ATB_Gauge_ScaleMark_Width_Default;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint8, float> ATB_Gauge_ScaleMark_Width;
    
    UEndCondorFortATBGauge();

protected:
    UFUNCTION(BlueprintCallable)
    FVector2D OnMeasureItem_GaugeDivisions(int32 ItemIndex);
    
};

