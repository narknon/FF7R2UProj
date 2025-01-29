#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndFieldKeyGuideList.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndFieldKeyGuideList : public UEndUserWidget {
    GENERATED_BODY()
public:
    UEndFieldKeyGuideList();

    UFUNCTION(BlueprintCallable)
    void OnCommandCellSetupShortcutAbilityPane(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandCellSetupSelectByCamera(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandCellSetupPlayFeel(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandCellSetupMiniGameBuggy(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandCellSetupGBike(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandCellSetupField(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandCellSetupChocoboRaceTutorial(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandCellSetupChocoboRace(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCommandCellSetupChainAbilityPane(UWidget* ItemWidget, int32 ItemIndex);
    
};

