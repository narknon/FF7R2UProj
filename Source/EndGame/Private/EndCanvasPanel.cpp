#include "EndCanvasPanel.h"

#include "EndCanvasPanelSlot.h"
#include "Components/SlateWrapperTypes.h"

#define LOCTEXT_NAMESPACE "UMG"

UEndCanvasPanel::UEndCanvasPanel() {
    this->bIsVariable = false;
    this->Visibility = ESlateVisibility::SelfHitTestInvisible;
    this->bExplicitChildZOrder = false;
    this->ProjectionMode = ECameraProjectionMode::Orthographic;
    this->FieldOfView = 90.00f;
}

void UEndCanvasPanel::SetProjectionMode(TEnumAsByte<ECameraProjectionMode::Type> InProjectionMode) {
    ProjectionMode = InProjectionMode;
}

void UEndCanvasPanel::SetFieldOfView(float InFieldOfView) {
    FieldOfView = InFieldOfView;
}

void UEndCanvasPanel::SetExplicitChildZOrder(bool bInExplicitChildZOrder) {
    bExplicitChildZOrder = bInExplicitChildZOrder;
}

void UEndCanvasPanel::SetContentColorAndOpacity(FLinearColor InContentColorAndOpacity) {
    ContentColorAndOpacity = InContentColorAndOpacity;
}

UClass* UEndCanvasPanel::GetSlotClass() const
{
    return UEndCanvasPanelSlot::StaticClass();
}

void UEndCanvasPanel::OnSlotAdded(UPanelSlot* InSlot)
{
    // Add the child to the live canvas if it already exists
    if ( MyCanvas.IsValid() )
    {
        CastChecked<UEndCanvasPanelSlot>(InSlot)->BuildSlot(MyCanvas.ToSharedRef());
    }
}

void UEndCanvasPanel::OnSlotRemoved(UPanelSlot* InSlot)
{
    // Remove the widget from the live slot if it exists.
    if ( MyCanvas.IsValid() && InSlot->Content)
    {
        TSharedPtr<SWidget> Widget = InSlot->Content->GetCachedWidget();
        if ( Widget.IsValid() )
        {
            MyCanvas->RemoveSlot(Widget.ToSharedRef());
        }
    }
}

TSharedRef<SWidget> UEndCanvasPanel::RebuildWidget()
{
    MyCanvas = SNew(SConstraintCanvas);

    for ( UPanelSlot* PanelSlot : Slots )
    {
        if ( UCanvasPanelSlot* TypedSlot = Cast<UCanvasPanelSlot>(PanelSlot) )
        {
            TypedSlot->Parent = this;
            TypedSlot->BuildSlot(MyCanvas.ToSharedRef());
        }
    }

    return MyCanvas.ToSharedRef();
}

UEndCanvasPanelSlot* UEndCanvasPanel::AddChildToCanvas(UWidget* Content) {
    return Cast<UEndCanvasPanelSlot>( Super::AddChild(Content) );
}

TSharedPtr<SConstraintCanvas> UEndCanvasPanel::GetCanvasWidget() const
{
    return MyCanvas;
}

bool UEndCanvasPanel::GetGeometryForSlot(int32 SlotIndex, FGeometry& ArrangedGeometry) const
{
    UEndCanvasPanelSlot* PanelSlot = CastChecked<UEndCanvasPanelSlot>(Slots[SlotIndex]);
    return GetGeometryForSlot(PanelSlot, ArrangedGeometry);
}

bool UEndCanvasPanel::GetGeometryForSlot(UEndCanvasPanelSlot* InSlot, FGeometry& ArrangedGeometry) const
{
    if ( InSlot->Content == nullptr )
    {
        return false;
    }

    TSharedPtr<SConstraintCanvas> Canvas = GetCanvasWidget();
    if ( Canvas.IsValid() )
    {
        FArrangedChildren ArrangedChildren(EVisibility::All);
        Canvas->ArrangeChildren(Canvas->GetCachedGeometry(), ArrangedChildren);

        for ( int32 ChildIndex = 0; ChildIndex < ArrangedChildren.Num(); ChildIndex++ )
        {
            if ( ArrangedChildren[ChildIndex].Widget == InSlot->Content->GetCachedWidget() )
            {
                ArrangedGeometry = ArrangedChildren[ChildIndex].Geometry;
                return true;
            }
        }
    }

    return false;
}

#if WITH_EDITOR

const FText UEndCanvasPanel::GetPaletteCategory()
{
    return LOCTEXT("Panel", "Panel");
}

#endif


#undef LOCTEXT_NAMESPACE