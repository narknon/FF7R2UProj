#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMateriaListNew.generated.h"

class UEndCanvasPanel;
class UEndImageSet;
class UEndMateriaListCellNew;
class UEndVirtualScrollBox;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMateriaListNew : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* Materia_List_Box;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* SummonPnl;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMateriaListCellNew* Materia_Summon_Cell;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImageSet* Icon_Summon;
    
    UEndMateriaListNew();

    UFUNCTION(BlueprintCallable)
    void OnMateriaListSetupItemLegacy(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMateriaListSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
};

