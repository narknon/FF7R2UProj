#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndEquipCategoryList.generated.h"

class UEndCanvasPanel;
class UEndEquipRemoveBtn;
class UEndVirtualScrollBox;
class UEndWeaponStatusSpAutoIcon;

UCLASS(Blueprintable, EditInlineNew)
class UEndEquipCategoryList : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* EquipCategoryList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndWeaponStatusSpAutoIcon* Sp_AutoIcon;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Pnl_AutoSettingBtn;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipRemoveBtn* Equip_RemoveBtn;
    
    UEndEquipCategoryList();

};

