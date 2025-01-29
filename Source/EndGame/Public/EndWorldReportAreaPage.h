#pragma once
#include "CoreMinimal.h"
#include "EndWorldReportProgressPage.h"
#include "EndWorldReportAreaPage.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndWorldReportAreaPage : public UEndWorldReportProgressPage {
    GENERATED_BODY()
public:
    UEndWorldReportAreaPage();

private:
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
    
    UFUNCTION(BlueprintCallable)
    void OnAreaReportListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
};

