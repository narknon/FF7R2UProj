#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndShopMenuPriceColors.h"
#include "EndUserWidget.h"
#include "EndShopMenu.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndShopMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float _SelectNumberSpan;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndShopMenuPriceColors _PriceColor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSoftObjectPath> _ShopTypeMarkIcons;
    
    UEndShopMenu();

    UFUNCTION(BlueprintCallable)
    void OnShopSwimCloudCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnShopSwimAerithCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnShopMoogleInfraIconSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnShopListCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnShopListCellCliked();
    
    UFUNCTION(BlueprintCallable)
    void OnShopGoldSaucerCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnShopEstCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnShopDefaultCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnShopDefaultCellCategolySetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnShopChocoboCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnShopChadolyCellSetup(UWidget* ItemWidget, int32 ItemIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnPressedShopTopMenu(int32 ItemIndex);
    
};

