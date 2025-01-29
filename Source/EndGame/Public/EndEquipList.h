#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndEquipList.generated.h"

class UEndCanvasPanel;
class UEndEquipRemoveBtn;
class UEndVirtualScrollBox;

UCLASS(Blueprintable, EditInlineNew)
class UEndEquipList : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* All_EquipLeftMenu;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* SelectList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEquipRemoveBtn* Equip_RemoveBtn;
    
    UEndEquipList();

};

