#pragma once
#include "CoreMinimal.h"
#include "EMooglePanicTriggerType.h"
#include "EndTriggerBox.h"
#include "EndMooglePanicTriggerBox.generated.h"

UCLASS(Blueprintable)
class AEndMooglePanicTriggerBox : public AEndTriggerBox {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EMooglePanicTriggerType TriggerEffect;
    
    AEndMooglePanicTriggerBox(const FObjectInitializer& ObjectInitializer);

};

