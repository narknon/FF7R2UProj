#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndPlayerLevelWindow.generated.h"

class UEndCanvasPanel;
class UEndPlayerLevelGauge;
class UEndPlayerLevelStatus;

UCLASS(Blueprintable, EditInlineNew)
class UEndPlayerLevelWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* AbilityBox;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndPlayerLevelGauge* PlayerLevel_Gauge;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndPlayerLevelStatus* PlayerLevel_Status;
    
    UEndPlayerLevelWindow();

};

