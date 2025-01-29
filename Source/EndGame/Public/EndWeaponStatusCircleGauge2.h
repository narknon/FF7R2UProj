#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndWeaponStatusCircleGauge2.generated.h"

class UEndCanvasPanel;
class UEndCircle;

UCLASS(Blueprintable, EditInlineNew)
class UEndWeaponStatusCircleGauge2 : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCircle* Gauge_Frame;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCircle* Gauge_TotalSp;
    
    UEndWeaponStatusCircleGauge2();

};

