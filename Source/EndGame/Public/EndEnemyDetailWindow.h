#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndEnemyDetailWindow.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndEnemyDetailWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndEnemyDetailWindow();

    UFUNCTION(BlueprintCallable)
    void OnStealListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnResistanceListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnResistanceIconListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnRareDropItemListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnDropItemListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnDebuffIconSetup(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBuffIconSetup(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBufferSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBattleLogSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBattleAbilitySetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnAcquisionSetup(UWidget* ItemWidget, int32 ItemIndex);
    
};

