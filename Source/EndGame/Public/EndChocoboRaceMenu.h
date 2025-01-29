#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndChocoboRaceMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndChocoboRaceMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndChocoboRaceMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnCourseListSetupItem(UWidget* ItemWidget, int32 InItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCourseListSelectedIndexChanged(int32 InItemIndex);
    
};

