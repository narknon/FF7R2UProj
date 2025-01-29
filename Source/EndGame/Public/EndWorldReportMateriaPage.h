#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndWorldReportProgressPage.h"
#include "EndWorldReportMateriaPage.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndWorldReportMateriaPage : public UEndWorldReportProgressPage {
    GENERATED_BODY()
public:
    UEndWorldReportMateriaPage();

private:
    UFUNCTION(BlueprintCallable)
    void OnMateriaInfoListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnMateriaInfoListMeasureItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMateriaDevelopListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBtnListSetupItemSummon(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBtnListSetupItemSea(UWidget* ItemWidget, int32 ItemIndex);
    
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

