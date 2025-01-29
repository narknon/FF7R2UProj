#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndNewSkillTreeTop.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndNewSkillTreeTop : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndNewSkillTreeTop();

private:
    UFUNCTION(BlueprintCallable)
    void OnMemberListSetupItem(UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMemberListSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMemberListPressedItem(int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnList00SetupItem(UWidget* InItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnList00SelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnList00PressedItem(int32 InItemIndex);
    
};

