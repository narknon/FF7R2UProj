#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndShootingGamePhaseIconWidget.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndShootingGamePhaseIconWidget : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndShootingGamePhaseIconWidget();

protected:
    UFUNCTION(BlueprintCallable)
    void OnMenuSelectedIndexChanged(int32 ItemIndex);
    
};

