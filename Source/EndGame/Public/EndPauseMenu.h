#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndPauseMenu.generated.h"

class UEndVirtualScrollBox;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndPauseMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* OptionScrollBox;
    
public:
    UEndPauseMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnListMenuSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListMenuPressedItem(int32 ItemIndex);
    
};

