#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMainWeaponUpgradeMenu.generated.h"

class USoundAttenuation;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMainWeaponUpgradeMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundAttenuation* SoundAttenuation;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndUserWidget* SpBox;
    
public:
    UEndMainWeaponUpgradeMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnYesButtonClicked();
    
    UFUNCTION(BlueprintCallable)
    void OnSkillListMenuSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnNoButtonClicked();
    
    UFUNCTION(BlueprintCallable)
    void OnMenuInFinish();
    
    UFUNCTION(BlueprintCallable)
    void OnCoreMenuSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
};

