#pragma once
#include "CoreMinimal.h"
#include "EndTriggerBox.h"
#include "EndTreasureBreakBox.generated.h"

UCLASS(Blueprintable)
class AEndTreasureBreakBox : public AEndTriggerBox {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDestroyWithoutBreak;
    
    AEndTreasureBreakBox(const FObjectInitializer& ObjectInitializer);

};

