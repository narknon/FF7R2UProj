#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCoreListNew.generated.h"

class UEndCanvasPanel;
class UEndVirtualScrollBox;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndCoreListNew : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* Core_List_Box;
    
    UEndCoreListNew();

    UFUNCTION(BlueprintCallable)
    void OnWeaponCoreListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
};

