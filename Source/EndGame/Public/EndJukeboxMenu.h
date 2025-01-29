#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndJukeboxMenu.generated.h"

class UEndBillboard;
class UWidget;
class UWidgetAnimation;

UCLASS(Blueprintable, EditInlineNew)
class UEndJukeboxMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndBillboard* CoverBillboard;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UWidgetAnimation* PlayingAnimation;
    
public:
    UEndJukeboxMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnSoundListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSoundListSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSoundListPressedItem(int32 ItemIndex);
    
};

