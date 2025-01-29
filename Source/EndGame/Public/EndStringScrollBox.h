#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "Layout/Margin.h"
#include "Styling/SlateTypes.h"
#include "Styling/SlateTypes.h"
#include "Styling/SlateColor.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/Widget.h"
#include "EEndMenuScrollBarPosition.h"
#include "EndStringScrollBox.generated.h"

class UEndFont;

UCLASS(Blueprintable)
class UEndStringScrollBox : public UWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FScrollBoxStyle WidgetStyle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FScrollBarStyle WidgetBarStyle;
    
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
    float WrapTextAt;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Text;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSlateColor ColorAndOpacity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor OutlineColorAndOpacity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndFont* Font;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D ShadowOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor ShadowColorAndOpacity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Outline;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 DesiredCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMargin SlotPadding;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMargin CullingBoundsExtension;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    TArray<UWidget*> ContentWidgets;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    TArray<UWidget*> CachedWidgets;
    
public:
    UEndStringScrollBox();

    UFUNCTION(BlueprintCallable)
    void SetWrapTextAt(float InWrapTextAt);
    
    UFUNCTION(BlueprintCallable)
    void SetText(const FString& InText);
    
    UFUNCTION(BlueprintCallable)
    void SetShadowOffset(FVector2D InShadowOffset);
    
    UFUNCTION(BlueprintCallable)
    void SetShadowColorAndOpacity(FLinearColor InShadowColorAndOpacity);
    
    UFUNCTION(BlueprintCallable)
    void SetScrollOffset(float NewScrollOffset);
    
    UFUNCTION(BlueprintCallable)
    void SetScrollBarPosition(EEndMenuScrollBarPosition InScrollBarPosition);
    
    UFUNCTION(BlueprintCallable)
    void SetPadding(FMargin InPadding);
    
    UFUNCTION(BlueprintCallable)
    void SetOutlineColorAndOpacity(FLinearColor InOutlineColorAndOpacity);
    
    UFUNCTION(BlueprintCallable)
    void SetOutline(bool bInOutline);
    
    UFUNCTION(BlueprintCallable)
    void SetFont(UEndFont* InFont);
    
    UFUNCTION(BlueprintCallable)
    void SetDesiredCount(int32 InDesiredCount);
    
    UFUNCTION(BlueprintCallable)
    void SetCullingBoundsExtension(FMargin InCullingBoundsExtension);
    
    UFUNCTION(BlueprintCallable)
    void SetColorAndOpacity(FSlateColor InColorAndOpacity);
    
    UFUNCTION(BlueprintCallable)
    void ScrollToStart();
    
    UFUNCTION(BlueprintCallable)
    void ScrollToEnd();
    
    UFUNCTION(BlueprintCallable)
    void RefreshItems();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FString GetText() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetScrollOffset() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    ESlateVisibility GetScrollBarVisibility() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetMaxScrollOffset(float InScrollHeight) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetLineCount() const;
    
};

