#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMenuSpeedMeterIcon.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndMenuSpeedMeterIcon : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float START;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Max;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MeterUpAnimationPower;
    
    UEndMenuSpeedMeterIcon();

};

