#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndUserWidget.h"
#include "EndMenuTalkItemList.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMenuTalkItemList : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndMenuTalkItemList();

private:
    UFUNCTION(BlueprintCallable)
    void OnList00SetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnList00MeasureItem(int32 ItemIndex);
    
};

