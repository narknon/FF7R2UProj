#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndItemModelWindow.h"
#include "EndItemWindow.generated.h"

class UEndBillboard;
class UEndCanvasPanel;
class UEndCategoryTitle;
class UEndCraftAreaInfoWindow;
class UEndEquipInfo;
class UEndEquipInfoDetailAbility;
class UEndEquipInfoDetailAccessory;
class UEndEquipInfoDetailCore;
class UEndEquipInfoDetailMateria;
class UEndItemCategoryList;
class UEndItemList;
class UEndNewSortWindow;
class UEndRecoverList;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndItemWindow : public UEndItemModelWindow {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBillboard* Billboard_Item;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipInfo* EquipInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCategoryTitle* CategoryTitle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndItemList* ItemList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipInfoDetailAbility* EquipInfoDetail_Ability;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipInfoDetailCore* EquipInfoDetail_Core;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipInfoDetailAccessory* EquipInfoDetail_Accessory;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipInfoDetailMateria* EquipInfoDetail_Materia;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndRecoverList* Recover_List;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNewSortWindow* Sort;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndItemCategoryList* CategoryList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCraftAreaInfoWindow* CraftAreaInfo;
    
    UEndItemWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnRecoverListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnRecoverListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnRecoverListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnRecoverListMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnItemTabListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnItemTabListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnItemTabListMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnItemListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnItemListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnItemListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnItemListMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnItemCategoryListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnItemCategoryListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnItemCategoryListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnItemCategoryListMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    bool OnItemButtonUnhover();
    
    UFUNCTION(BlueprintCallable)
    bool OnItemButtonHover();
    
};

