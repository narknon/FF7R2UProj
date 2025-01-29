#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EPlayerType.h"
#include "EndUserWidget.h"
#include "EndQuickMateriaMenu.generated.h"

class UEndBillboard;
class UEndCanvasPanel;
class UEndEquipmentMateriaInfoWindow;
class UEndImage;
class UEndQuickMateriaList;
class UEndSortWindow;
class UEndTextBlock;
class UTexture2D;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndQuickMateriaMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndQuickMateriaList* List_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndQuickMateriaList* List_1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndQuickMateriaList* List_2;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndQuickMateriaList* List_3;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndQuickMateriaList* List_4;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndUserWidget* EquipCell_Top;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndUserWidget* MateriaListMenu;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImage* Billboard_Materia;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBillboard* Billboard_CharaImg;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipmentMateriaInfoWindow* SkillList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* BtnPnl2;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* BtnPnl3;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Btn3;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSortWindow* SortList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UTexture2D*> _MateriaImages;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<EPlayerType, FSoftObjectPath> _CharaImagePaths;
    
public:
    UEndQuickMateriaMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnSummonMateriaSlotPressed();
    
    UFUNCTION(BlueprintCallable)
    void OnSortListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSlotPressed();
    
    UFUNCTION(BlueprintCallable)
    void OnSlotIndexChanged();
    
    UFUNCTION(BlueprintCallable)
    void OnMateriaMenuSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMateriaMenuSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMateriaMenuPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnMateriaMenuMeasureItem(int32 CellIndex);
    
};

