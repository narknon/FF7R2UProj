#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndGambitInGameMenuWidget.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndGambitInGameMenuWidget : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndGambitInGameMenuWidget();

    UFUNCTION(BlueprintCallable)
    void OnResultInfoSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
};

