#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndBoxing3DBattlerResult.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndBoxing3DBattlerResult : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndBoxing3DBattlerResult();

private:
    UFUNCTION(BlueprintCallable)
    void OnPrizeListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
};

