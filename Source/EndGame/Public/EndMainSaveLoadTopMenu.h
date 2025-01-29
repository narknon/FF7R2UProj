#pragma once
#include "CoreMinimal.h"
#include "EndMainMenuWindow.h"
#include "Templates/SubclassOf.h"
#include "EndMainSaveLoadTopMenu.generated.h"

class UEndUserWidget;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMainSaveLoadTopMenu : public UEndMainMenuWindow {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndUserWidget> SaveLoadMenuWidgetClass;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndUserWidget* Throbber;
    
public:
    UEndMainSaveLoadTopMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuPressedItem(int32 ItemIndex);
    
};

