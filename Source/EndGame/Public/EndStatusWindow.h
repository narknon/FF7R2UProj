#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndMainMenuWindow.h"
#include "EndStatusWindow.generated.h"

class UEndCanvasPanel;
class UEndCategoryTitle;
class UEndEquipInfo;
class UEndMemberList;
class UEndStatusAbilityList;
class UEndStatusCellTitle;
class UEndStatusIconList;
class UEndStatusList;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndStatusWindow : public UEndMainMenuWindow {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCategoryTitle* CategoryTitle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberList* MemberList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipInfo* EquipInfo_01;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipInfo* EquipInfo_02;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipInfo* EquipInfo_03;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndStatusIconList* StatusList_IconList_01;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndStatusCellTitle* Title_Atk_Attribution;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndStatusCellTitle* Title_Def_Attribution;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndStatusList* StatusList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndStatusIconList* StatusList_IconList_02;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndStatusIconList* StatusList_IconList_03;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndStatusIconList* StatusList_IconList_04;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndStatusIconList* StatusList_IconList_05;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndStatusAbilityList* StatusAbilityList;
    
    UEndStatusWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnWeaponCoreSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnWeaponCoreMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSummonSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnSummonMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnPassiveListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnPassiveListMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMemberListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMemberListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMemberListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnMemberListMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMagicSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnMagicMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnLimitSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnLimitMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnChainActionSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnChainActionMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnChainAbilitySetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnChainAbilityMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnAbilitySetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnAbilityMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnAbilityListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnAbilityListMeasureItem(int32 CellIndex);
    
};

