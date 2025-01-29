#pragma once
#include "CoreMinimal.h"
#include "EPlayerType.h"
#include "EndMainMenuWindow.h"
#include "EndMainWeaponUpgradeEquipMenu.generated.h"

class UEndCanvasPanel;
class UEndEquipmentMateriaInfoWindow;
class UEndImage;
class UEndSortWindow;
class UEndUserWidget;
class UEndWeaponUpgradeCircleGauge;
class UEndWeaponUpgradeCoreRingWindow;
class UPaperSprite;
class UTexture2D;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMainWeaponUpgradeEquipMenu : public UEndMainMenuWindow {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UPaperSprite*> _CharaImages;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UTexture2D*> _DetailCharaImages;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipmentMateriaInfoWindow* SkillList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndWeaponUpgradeCircleGauge* CircleGauge2;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndUserWidget* SpAutoList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSortWindow* SortList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Pnl_Core;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndWeaponUpgradeCoreRingWindow* Core_Ring;
    
public:
    UEndMainWeaponUpgradeEquipMenu();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void UpdateCharaImage(EPlayerType PlayerType, UEndImage* Widget, UPaperSprite* Sprite);
    
private:
    UFUNCTION(BlueprintCallable)
    void OnSpListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSpListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSpListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSortListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMemberMenuSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMemberMenuSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMemberMenuPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEquipMenuSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEquipMenuSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEquipMenuPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCoreListSetupItemYuffie(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCoreListSetupItemTifa(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCoreListSetupItemSonon(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCoreListSetupItemRedxiii(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCoreListSetupItemCloud(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCoreListSetupItemBarret(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCoreListSetupItemAerith(UWidget* ItemWidget, int32 CellIndex);
    
};

