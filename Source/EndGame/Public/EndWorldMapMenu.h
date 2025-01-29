#pragma once
#include "CoreMinimal.h"
#include "EndMenuWorldMapAreaSetting.h"
#include "EndUserWidget.h"
#include "EndWorldMapMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndWorldMapMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndMenuWorldMapAreaSetting> AreaSettings;
    
    UEndWorldMapMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuScrollBoxSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuScrollBoxSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuScrollBoxPressedItem(int32 ItemIndex);
    
};

