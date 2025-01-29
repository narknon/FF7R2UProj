#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndResearchTargetList.generated.h"

class UEndImageSet;
class UEndTextBlock;
class UEndVirtualScrollBox;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndResearchTargetList : public UEndUserWidget {
    GENERATED_BODY()
public:
    DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnResearchTargetSetupItem, int32, Category, UWidget*, ItemWidget, int32, ItemIndex);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResearchTargetSelectedIndexChanged, int32, Category, int32, ItemIndex);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResearchTargetPressedItem, int32, Category, int32, ItemIndex);
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* BtnList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_AreaName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImageSet* Icon;
    
    UEndResearchTargetList();

private:
    UFUNCTION(BlueprintCallable)
    void OnSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnPressedItem(int32 CellIndex);
    
};

