#pragma once
#include "CoreMinimal.h"
#include "EndMapJournalMenuWindow.h"
#include "EndStoryMenu.generated.h"

class UWidget;
class UWidgetAnimation;

UCLASS(Blueprintable, EditInlineNew)
class UEndStoryMenu : public UEndMapJournalMenuWindow {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UWidgetAnimation* CurrentAnimation;
    
public:
    UEndStoryMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuPressedItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    bool OnLeftMenuCanFocus(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnChapterChangeBtnSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
};

