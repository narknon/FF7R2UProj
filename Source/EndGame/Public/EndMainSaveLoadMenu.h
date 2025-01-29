#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMainSaveLoadMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMainSaveLoadMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndUserWidget* Throbber;
    
public:
    UEndMainSaveLoadMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnSaveDataSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSaveDataSelectedIndexChanged(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSaveDataPressedItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSaveDataCancelled();
    
};

