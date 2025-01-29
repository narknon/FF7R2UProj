#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndUserWidget.h"
#include "EndStoryDetailWindow.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndStoryDetailWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndStoryDetailWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnQuestInfoListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnQuestInfoListMeasureItem(int32 ItemIndex);
    
};

