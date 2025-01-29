#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EPlayerType.h"
#include "EndMainMenuWindow.h"
#include "EndMainStatusMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMainStatusMenu : public UEndMainMenuWindow {
    GENERATED_BODY()
public:
    UEndMainStatusMenu();

private:
    UFUNCTION(BlueprintCallable)
    void UpdateStatusPanel(EPlayerType PlayerType);
    
    UFUNCTION(BlueprintCallable)
    void UpdatePlayerStatusInfo(int32 CellIndex, EPlayerType PlayerType);
    
    UFUNCTION(BlueprintCallable)
    void UpdateEquipmentInfo(int32 CellIndex, EPlayerType PlayerType);
    
    UFUNCTION(BlueprintCallable)
    void UpdateDescription(EPlayerType PlayerType);
    
    UFUNCTION(BlueprintCallable)
    void SetupDescriptionTitle();
    
    UFUNCTION(BlueprintCallable)
    void OnSetupSummonItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSetupStatusItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSetupMagicItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSetupLimitItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSetupAbilityItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnMeasureSummonItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnMeasureStatusItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnMeasureMagicItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnMeasureLimitItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnMeasureAbilityItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLeftMenuSelectedIndexChanged(int32 CellIndex);
    
};

