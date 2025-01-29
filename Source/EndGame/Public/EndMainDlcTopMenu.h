#pragma once
#include "CoreMinimal.h"
#include "EndMainMenuWindow.h"
#include "EndMainDlcTopMenu.generated.h"

class UEndBillboard;
class UEndStringScrollBox;
class UEndVirtualScrollBox;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMainDlcTopMenu : public UEndMainMenuWindow {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* ReportList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBillboard* Billboard_Img;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndStringScrollBox* DlcInfo;
    
public:
    UEndMainDlcTopMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnSetupItemInternal(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSelectedIndexChangedInternal(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnPressedItemInternal(int32 CellIndex);
    
};

