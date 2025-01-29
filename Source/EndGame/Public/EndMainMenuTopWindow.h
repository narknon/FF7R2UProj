#pragma once
#include "CoreMinimal.h"
#include "EndMainMenuWindow.h"
#include "EndMainMenuTopWindow.generated.h"

class UEndTopContent;
class UEndUserWidget;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMainMenuTopWindow : public UEndMainMenuWindow {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndUserWidget* PartyLevel;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTopContent* TopContent2;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndUserWidget* Throbber;
    
public:
    UEndMainMenuTopWindow();

    UFUNCTION(BlueprintCallable)
    bool SetupPartySlot(int32 SlotIndex);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnPlaySlotAnimation(bool IsShow);
    
private:
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuPressedItem(int32 ItemIndex);
    
};

