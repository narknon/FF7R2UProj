#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndMapJournalMenuWindow.h"
#include "EndQuestMenu2.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndQuestMenu2 : public UEndMapJournalMenuWindow {
    GENERATED_BODY()
public:
    UEndQuestMenu2();

private:
    UFUNCTION(BlueprintCallable)
    void OnQuestInfoListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnQuestInfoListMeasureItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuScrollBoxSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuScrollBoxSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnLeftMenuScrollBoxMeasureItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnAreaChangeBtnSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
};

