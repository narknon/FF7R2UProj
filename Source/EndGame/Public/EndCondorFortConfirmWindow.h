#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCondorFortConfirmWindow.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndCondorFortConfirmWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndCondorFortConfirmWindow();

protected:
    UFUNCTION(BlueprintCallable)
    void OnSetup_Options(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnPressed_Button();
    
};

