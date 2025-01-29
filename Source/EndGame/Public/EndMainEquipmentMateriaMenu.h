#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EEquipmentCategoryMain.h"
#include "EPlayerType.h"
#include "EndMainMenuWindow.h"
#include "Templates/SubclassOf.h"
#include "EndMainEquipmentMateriaMenu.generated.h"

class UEndBillboard;
class UEndCanvasPanel;
class UEndEquipmentMateriaInfoWindow;
class UEndImage;
class UEndQuickMateriaMenu;
class UEndSortWindow;
class UEndTextBlock;
class UEndUserWidget;
class UTexture2D;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMainEquipmentMateriaMenu : public UEndMainMenuWindow {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSoftObjectPath> _CharaImagePaths;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UTexture2D*> _MateriaImages;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImage* Billboard_Materia;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBillboard* Billboard_Weapon_Top;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipmentMateriaInfoWindow* SkillList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Title;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* BtnRemove;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_BtnIcon;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Btn;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndUserWidget* AccessoryInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSortWindow* SortList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndUserWidget> MateriaQuickWidget;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndQuickMateriaMenu* _MateriaQuickWindow;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndUserWidget* MateriaList;
    
public:
    UEndMainEquipmentMateriaMenu();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void UpdateStatusPanelWithMateria(EPlayerType PlayerType, EEquipmentCategoryMain EquipType, int32 SlotIndex, int32 OrigMateriaIndex, int32 TargetMateriaIndex);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void UpdateStatusPanelWithEquipment(EPlayerType PlayerType, EEquipmentCategoryMain EquipType, const FName& EquipID, int32 EquipIndex);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void UpdateStatusPanel(EPlayerType PlayerType);
    
private:
    UFUNCTION(BlueprintCallable)
    void OnWeaponCoreSlotPressed();
    
    UFUNCTION(BlueprintCallable)
    void OnWeaponCoreSlotIndexChanged();
    
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
    FVector2D OnMateriaMenuMeasureItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEquipMenuSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEquipMenuSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEquipMenuPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnEquipMenuMeasureItem(int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEquipCategoryMenuSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEquipCategoryMenuSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEquipCategoryMenuPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCharaMenuSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCharaMenuSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCharaMenuPressedItem(int32 CellIndex);
    
};

