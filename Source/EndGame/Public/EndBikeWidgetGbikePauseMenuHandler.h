#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndBikeWidgetGbikePauseMenuHandler.generated.h"

class UWidget;

UCLASS(Blueprintable)
class UEndBikeWidgetGbikePauseMenuHandler : public UObject {
    GENERATED_BODY()
public:
    UEndBikeWidgetGbikePauseMenuHandler();

    UFUNCTION(BlueprintCallable)
    void OnCommandClicked(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
};

