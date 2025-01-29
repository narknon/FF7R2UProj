#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndMainMenuWindow.h"
#include "EndEnemyReportMenu.generated.h"

class UEndStringScrollBox;
class UEndTextBlock;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndEnemyReportMenu : public UEndMainMenuWindow {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndStringScrollBox* _DetailFlavorTipsDescriptionScrollBox;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndTextBlock* _DetailScrollTextBlock;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DetailFadeInOutLenght;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float CharacterDitherFadeInLenght;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RotationYMin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RotationYMax;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RotationYDefault;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RotationXSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RotationYSpeed;
    
    UEndEnemyReportMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnStealListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnResistanceListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnResistanceIconListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnRareDropItemListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEnemyListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEnemyListSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnEnemyListPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnEnemyListMeasureItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnDropItemListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnDetailBattleLogListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnDetailAreaListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnDebuffIconSetup(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBuffIconSetup(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnBattleLogListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnAreaListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnActionTypeListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnAbilityListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
};

