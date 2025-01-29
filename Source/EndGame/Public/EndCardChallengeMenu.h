#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCardChallengeMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndCardChallengeMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndCardChallengeMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnTermListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnTabMenuSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSelectListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSelectListSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSelectListPressedItem(int32 ItemIndex);
    
};

