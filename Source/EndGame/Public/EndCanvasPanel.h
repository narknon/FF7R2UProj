#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Camera/CameraTypes.h"
#include "Components/PanelWidget.h"
#include "Components/Widget.h"
#include "EndCanvasPanel.generated.h"

class UEndCanvasPanelSlot;
class UWidget;

UCLASS(Blueprintable)
class ENDGAME_API UEndCanvasPanel : public UPanelWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor ContentColorAndOpacity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UWidget::FGetLinearColor ContentColorAndOpacityDelegate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bExplicitChildZOrder;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ECameraProjectionMode::Type> ProjectionMode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FieldOfView;
    
    UEndCanvasPanel();

    UFUNCTION(BlueprintCallable)
    void SetProjectionMode(TEnumAsByte<ECameraProjectionMode::Type> InProjectionMode);
    
    UFUNCTION(BlueprintCallable)
    void SetFieldOfView(float InFieldOfView);
    
    UFUNCTION(BlueprintCallable)
    void SetExplicitChildZOrder(bool bInExplicitChildZOrder);
    
    UFUNCTION(BlueprintCallable)
    void SetContentColorAndOpacity(FLinearColor InContentColorAndOpacity);
    
    UFUNCTION(BlueprintCallable)
    UEndCanvasPanelSlot* AddChildToCanvas(UWidget* Content);

    /** Gets the underlying native canvas widget if it has been constructed */
    TSharedPtr<class SConstraintCanvas> GetCanvasWidget() const;

    /** Computes the geometry for a particular slot based on the current geometry of the canvas. */
    bool GetGeometryForSlot(int32 SlotIndex, FGeometry& ArrangedGeometry) const;

    /** Computes the geometry for a particular slot based on the current geometry of the canvas. */
    bool GetGeometryForSlot(UEndCanvasPanelSlot* Slot, FGeometry& ArrangedGeometry) const;

#if WITH_EDITOR
    // UWidget interface
    virtual const FText GetPaletteCategory() override;
    // End UWidget interface

    // UWidget interface
    virtual bool LockToPanelOnDrag() const override
    {
        return true;
    }
    // End UWidget interface
#endif

protected:
    
    // UPanelWidget
    virtual UClass* GetSlotClass() const override;
    virtual void OnSlotAdded(UPanelSlot* Slot) override;
    virtual void OnSlotRemoved(UPanelSlot* Slot) override;
    // End UPanelWidget
    
protected:
    
    TSharedPtr<class SConstraintCanvas> MyCanvas;

protected:
    // UWidget interface
    virtual TSharedRef<SWidget> RebuildWidget() override;
    // End of UWidget interface 
};

