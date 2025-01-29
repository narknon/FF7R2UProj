#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EChocoboEquipPartsType.h"
#include "EndUserWidget.h"
#include "EndChocoboStableMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndChocoboStableMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndChocoboStableMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnTabMenuSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnTabMenuMeasureItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSkillListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnHeadBoxEquipSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnFootBoxEquipSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnChangePartsColor(EChocoboEquipPartsType EditType, FColor Color0, FColor Color1);
    
    UFUNCTION(BlueprintCallable)
    void OnBodyBoxEquipSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
};

