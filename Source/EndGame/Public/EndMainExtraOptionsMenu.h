#pragma once
#include "CoreMinimal.h"
#include "EndMainOptionsMenuBase.h"
#include "EndMainExtraOptionsMenu.generated.h"

class UWidget;

UCLASS(Blueprintable)
class UEndMainExtraOptionsMenu : public UEndMainOptionsMenuBase {
    GENERATED_BODY()
public:
    UEndMainExtraOptionsMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnSettingListSetupItem(UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSettingListSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSettingListPressedItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSelectListSetupItem(UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSelectListSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSelectListPressedItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuScrollBoxSetupItem(UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuScrollBoxSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuScrollBoxPressedItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnGaugeSetupItem(UWidget* InItemWidget, int32 InItemIndex);
    
};

