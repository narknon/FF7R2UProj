#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCmdLinkupPane.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndCmdLinkupPane : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndCmdLinkupPane();

    UFUNCTION(BlueprintCallable)
    void OnLinkupCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
};

