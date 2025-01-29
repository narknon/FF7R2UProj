#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndWorldReportProgressPage.h"
#include "EndWorldReportVrExPage.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndWorldReportVrExPage : public UEndWorldReportProgressPage {
    GENERATED_BODY()
public:
    UEndWorldReportVrExPage();

private:
    UFUNCTION(BlueprintCallable)
    void OnTermListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnTermListMeasureItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnPrizeListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBtnListSetupItem6(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBtnListSetupItem5(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBtnListSetupItem4(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBtnListSetupItem3(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBtnListSetupItem2(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBtnListSetupItem1(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBtnListSetupItem0(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnAreaReportListSetupItem(UWidget* ItemWidget, int32 ItemIndex);
    
};

