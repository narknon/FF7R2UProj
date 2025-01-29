#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndPianoMusicSelectListWidget.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndPianoMusicSelectListWidget : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndPianoMusicSelectListWidget();

protected:
    UFUNCTION(BlueprintCallable)
    void OnSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMenuSelectedIndexChanged(int32 ItemIndex);
    
};

