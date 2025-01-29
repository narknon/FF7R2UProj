#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndMainEquipInfoWindowBase.h"
#include "EndShopItemInfoWindow.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndShopItemInfoWindow : public UEndMainEquipInfoWindowBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float _InfoTextWrapSize;
    
    UEndShopItemInfoWindow();

protected:
    UFUNCTION(BlueprintCallable)
    FVector2D OnMeasureInfoListSize(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMateriaInfoListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListCompareItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnListCompare1Item(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnCoreListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
};

