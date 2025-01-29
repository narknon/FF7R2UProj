#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndChocoboCaptureCommandMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndChocoboCaptureCommandMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndChocoboCaptureCommandMenu();

    UFUNCTION(BlueprintCallable)
    void OnSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
};

