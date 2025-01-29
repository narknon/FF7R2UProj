#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndWorldReportProgressPage.h"
#include "EndWorldReportEnemyPage.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndWorldReportEnemyPage : public UEndWorldReportProgressPage {
    GENERATED_BODY()
public:
    UEndWorldReportEnemyPage();

private:
    UFUNCTION(BlueprintCallable)
    void OnTermListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnTermListMeasureItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnResearchTargetListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBtnListSetupItemNibel(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBtnListSetupItemJunon(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBtnListSetupItemGongaga(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBtnListSetupItemGlasslands(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBtnListSetupItemCosmo(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBtnListSetupItemCorel(UWidget* ItemWidget, int32 ItemIndex);
    
};

