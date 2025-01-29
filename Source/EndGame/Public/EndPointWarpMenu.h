#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndPointWarpMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndPointWarpMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndPointWarpMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnListItemSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListItemSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListItemPressedItem(int32 ItemIndex);
    
};

