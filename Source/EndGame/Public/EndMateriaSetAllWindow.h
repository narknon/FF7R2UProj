#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndUserWidget.h"
#include "EndMateriaSetAllWindow.generated.h"

class UEndCanvasPanel;
class UEndMateriaSetInfoListWindow;
class UEndMateriaSetSelectListWindow;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMateriaSetAllWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMateriaSetSelectListWindow* MateriaSet_SelectList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMateriaSetInfoListWindow* MateriaSet_InfoList;
    
    UEndMateriaSetAllWindow();

private:
    UFUNCTION(BlueprintCallable)
    void OnMateriaSetSetupItem(UWidget* ItemWidget, int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMateriaSetSelectedIndexChanged(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    void OnMateriaSetPressedItem(int32 CellIndex);
    
    UFUNCTION(BlueprintCallable)
    FVector2D OnMateriaSetMeasureItem(int32 CellIndex);
    
};

