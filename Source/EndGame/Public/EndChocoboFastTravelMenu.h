#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndChocoboFastTravelMenu.generated.h"

class UWidget;
class UWidgetAnimation;

UCLASS(Blueprintable, EditInlineNew)
class UEndChocoboFastTravelMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UWidgetAnimation* PlayingAnimation;
    
public:
    UEndChocoboFastTravelMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnPointsListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnPointsListPressedItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnPointsListIndexChanged(int32 ItemIndex);
    
};

