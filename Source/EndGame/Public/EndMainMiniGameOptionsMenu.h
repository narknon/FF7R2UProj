#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndMainOptionsMenuBase.h"
#include "EndMainMiniGameOptionsMenu.generated.h"

class UWidget;

UCLASS(Blueprintable)
class UEndMainMiniGameOptionsMenu : public UEndMainOptionsMenuBase {
    GENERATED_BODY()
public:
    UEndMainMiniGameOptionsMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnOptionListKeyboardSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnOptionListKeyboardSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnOptionListKeyboardPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnOptionListKeyboardMeasureItem(int32 ItemIndex);
    
};

