#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndLoadingScreen.generated.h"

class UEndBillboard;
class UEndTextBlock;
class UEndVirtualScrollBox;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndLoadingScreen : public UEndUserWidget {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBillboard* Img_BG;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* StoneBox;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_TipsTitle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Info;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Goto;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Category;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBillboard* Billboard_QuestThumbnail;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_QuestStep;
    
public:
    UEndLoadingScreen();

private:
    UFUNCTION(BlueprintCallable)
    void OnTipListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnTipListSelectedIndexChanged(int32 CellIndex);
    
};

