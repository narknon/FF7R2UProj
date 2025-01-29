#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndQuestBoardMenu.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndQuestBoardMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndQuestBoardMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnQuestButtonClicked();
    
};

