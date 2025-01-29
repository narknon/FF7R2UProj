#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndEventProgressDisplay.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndEventProgressDisplay : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OffsetForNaviMap;
    
    UEndEventProgressDisplay();

};

