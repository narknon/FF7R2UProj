#pragma once
#include "CoreMinimal.h"
#include "EndMapJournalMenuWindow.h"
#include "EndQuestMenu.generated.h"

class UWidget;
class UWidgetAnimation;

UCLASS(Blueprintable, EditInlineNew)
class UEndQuestMenu : public UEndMapJournalMenuWindow {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UWidgetAnimation* CurrentAnimation;
    
public:
    UEndQuestMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnQuestScrollBoxSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnQuestScrollBoxPressedItem(int32 ItemIndex);
    
};

