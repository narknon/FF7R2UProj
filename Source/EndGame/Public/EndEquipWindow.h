#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndItemModelWindow.h"
#include "EndEquipWindow.generated.h"

class UEndAutoSettingList;
class UEndCanvasPanel;
class UEndCategoryTitle;
class UEndCategoryTitleMember;
class UEndEquipCategoryList;
class UEndEquipInfo;
class UEndEquipInfoDetailAbility;
class UEndEquipInfoDetailAccessory;
class UEndEquipInfoDetailCore;
class UEndEquipInfoDetailMateria;
class UEndEquipList;
class UEndMateriaListAll;
class UEndMateriaSelectList;
class UEndMemberEquipList;
class UEndMemberList;
class UEndNewSortWindow;
class UEndPartyName;
class UEndStatusList;
class UEndTextBlock;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndEquipWindow : public UEndItemModelWindow {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Pnl_MenuAll;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCategoryTitle* CategoryTitle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberList* MemberList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndStatusList* StatusList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndPartyName* PlayerName_01;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndPartyName* PlayerName_02;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndPartyName* PlayerName_03;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberEquipList* MemberEquipList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCategoryTitleMember* CategoryTitle_Member;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_ListTitle_Category;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_ListTitle_Category_1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMateriaListAll* Materia_List_All;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipCategoryList* Equip_CategoryList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipList* EquipList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Pnl_AutoSettingBtn;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipInfo* EquipInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipInfoDetailAbility* EquipInfoDetail_Ability;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipInfoDetailAccessory* EquipInfoDetail_Accessory;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipInfoDetailMateria* EquipInfoDetail_Materia;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipInfoDetailCore* EquipInfoDetail_Core;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMateriaSelectList* Materia_SelectList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNewSortWindow* Sort;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndAutoSettingList* AutoSettingList;
    
    UEndEquipWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnWeaponMateriaSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnWeaponMateriaSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnWeaponMateriaPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnWeaponMateriaMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnWeaponCoreSkillInfoListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnWeaponCoreSkillInfoListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnWeaponCoreSkillInfoListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnWeaponCoreSkillInfoListMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnWeaponCoreSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnWeaponCoreSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnWeaponCorePressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnWeaponCoreMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnWeaponCoreEditListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnWeaponCoreEditListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnWeaponCoreEditListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSummonMateriaSelectedIndexChanged();
    
    UFUNCTION(BlueprintCallable)
    void OnSummonMateriaPressedItem();
    
    UFUNCTION(BlueprintCallable)
    void OnSummonMateriaEditListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSummonMateriaEditListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSummonMateriaEditListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSortListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMemberListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMemberListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMemberListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnMemberListMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMateriaEditListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMateriaEditListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMateriaEditListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMateriaEditCategoryListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMateriaEditCategoryListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMateriaEditCategoryListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnMateriaEditCategoryListMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEquipIdListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEquipIdListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEquipIdListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnEquipIdListMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEquipCategorySetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEquipCategorySelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEquipCategoryPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnEquipCategoryMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEditListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEditListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEditListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnEditListMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnAutoSettingSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnAutoSettingSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnAutoSettingPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnAutoSettingMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnArmorMateriaSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnArmorMateriaSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnArmorMateriaPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnArmorMateriaMeasureItem(int32 CellIndex);
    
};

