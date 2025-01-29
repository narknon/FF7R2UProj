#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Input/Events.h"
#include "Types/SlateEnums.h"
#include "Layout/Margin.h"
#include "Styling/SlateTypes.h"
#include "Styling/SlateTypes.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/Widget.h"
#include "EEndMenuScrollBarPosition.h"
#include "Templates/SubclassOf.h"
#include "EndVirtualScrollBox.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndVirtualScrollBox : public UWidget {
    GENERATED_BODY()
public:
    DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnSetupItem, UWidget*, ItemWidget, int32, ItemIndex);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedIndexChanged, int32, ItemIndex);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPressedItem, int32, ItemIndex);
    DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(FVector2D, FOnMeasureItem, int32, ItemIndex);
    DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCleanupItem, UWidget*, ItemWidget);
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FScrollBoxStyle WidgetStyle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FScrollBarStyle WidgetBarStyle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EOrientation> Orientation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ESlateVisibility ScrollBarVisibility;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D ScrollbarThickness;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool AlwaysShowScrollbar;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndMenuScrollBarPosition ScrollBarPosition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMargin ClippingPadding;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool SupportsPageScroll;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool SupportsKeyDown;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool VariableSizeItem;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UWidget> ContentClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UWidget> CursorClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 ItemCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 DesiredCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMargin SlotPadding;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMargin CursorBoundsExtension;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMargin CullingBoundsExtension;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOnSetupItem OnSetupItem;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOnMeasureItem OnMeasureItem;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOnPressedItem OnPressedItem;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOnSelectedIndexChanged OnSelectedIndexChanged;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    TArray<UWidget*> ContentWidgets;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    TArray<UWidget*> CachedWidgets;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UWidget* CursorWidget;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UWidget* CachedCursor;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CursorEffectName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D CursorEffectOffset;
    
    UEndVirtualScrollBox();

    UFUNCTION(BlueprintCallable)
    void SetSupportsPageScroll(bool bInSupportsPageScroll);
    
    UFUNCTION(BlueprintCallable)
    void SetSupportsKeyDown(bool bInSupportsKeyDown);
    
    UFUNCTION(BlueprintCallable)
    void SetSupportsFocus(bool bInSupportsFocus);
    
    UFUNCTION(BlueprintCallable)
    void SetSelectedIndexWithCause(int32 UserIndex, int32 SlotIndex, EFocusCause FocusCause, bool InAnimateScroll, bool ForceCallback, UWidget* InRootWidget);
    
    UFUNCTION(BlueprintCallable)
    void SetSelectedIndex(int32 UserIndex, int32 SlotIndex, bool InAnimateScroll, bool ForceCallback, UWidget* InRootWidget);
    
    UFUNCTION(BlueprintCallable)
    void SetScrollOffset(float NewScrollOffset, bool AnimateScroll);
    
    UFUNCTION(BlueprintCallable)
    void SetScrollBarPosition(EEndMenuScrollBarPosition InScrollBarPosition);
    
    UFUNCTION(BlueprintCallable)
    void SetPadding(FMargin InPadding);
    
    UFUNCTION(BlueprintCallable)
    void SetItemCount(int32 InItemCount);
    
    UFUNCTION(BlueprintCallable)
    void SetHasVariableSizeItem(bool bInVariableSizeItem);
    
    UFUNCTION(BlueprintCallable)
    void SetForceHovered(bool bInHovered);
    
    UFUNCTION(BlueprintCallable)
    void SetDesiredCount(int32 InDesiredCount);
    
    UFUNCTION(BlueprintCallable)
    void SetCursorBoundsExtension(FMargin InCursorBoundsExtension);
    
    UFUNCTION(BlueprintCallable)
    void SetCullingBoundsExtension(FMargin InCullingBoundsExtension);
    
    UFUNCTION(BlueprintCallable)
    void ScrollWidgetIntoView(UWidget* WidgetToFind, bool AnimateScroll);
    
    UFUNCTION(BlueprintCallable)
    void ScrollToStart();
    
    UFUNCTION(BlueprintCallable)
    void ScrollToEnd();
    
    UFUNCTION(BlueprintCallable)
    void RefreshItems();
    
    UFUNCTION(BlueprintCallable)
    void RefreshItem(int32 Index);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetSelectedIndex(int32 UserIndex) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetScrollOffset() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    ESlateVisibility GetScrollBarVisibility() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetMaxScrollOffset() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool GetIsForceHovered() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UWidget* GetCursorWidget() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UWidget* GetChildAt(int32 Index) const;
    
};

