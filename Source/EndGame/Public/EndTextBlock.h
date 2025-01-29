#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "Framework/Text/TextLayout.h"
#include "Layout/Margin.h"
#include "Styling/SlateColor.h"
#include "Components/Widget.h"
#include "EEndMenuTextButtonLayoutMode.h"
#include "EndTextBlock.generated.h"

class UEndFont;

UCLASS(Blueprintable)
class ENDGAME_API UEndTextBlock : public UWidget {
    GENERATED_BODY()
public:
    DECLARE_DYNAMIC_DELEGATE_RetVal(FString, FGetString);
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ETextJustify::Type> Justification;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool AutoWrapText;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool AutoShrinkText;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float WrapTextAt;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMargin Margin;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LineHeightPercentage;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Text;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FGetString TextDelegate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSlateColor ColorAndOpacity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UWidget::FGetSlateColor ColorAndOpacityDelegate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Gradient;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSlateColor BottomColorAndOpacity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UWidget::FGetSlateColor BottomColorAndOpacityDelegate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor OutlineColorAndOpacity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UWidget::FGetLinearColor OutlineColorAndOpacityDelegate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndFont* Font;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D ShadowOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor ShadowColorAndOpacity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UWidget::FGetLinearColor ShadowColorAndOpacityDelegate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MinDesiredWidth;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EBlendMode> BlendMode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Outline;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool AllowMacro;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool LeftAlignedCenter;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool AutoUpdateButtons;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool ColoredButtons;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndMenuTextButtonLayoutMode ButtonLayoutMode;
    
    UEndTextBlock();

    UFUNCTION(BlueprintCallable)
    void SetWrapTextAt(float InWrapTextAt);
    
    UFUNCTION(BlueprintCallable)
    void SetText(const FString& InText);
    
    UFUNCTION(BlueprintCallable)
    void SetShadowOffset(FVector2D InShadowOffset);
    
    UFUNCTION(BlueprintCallable)
    void SetShadowColorAndOpacity(FLinearColor InShadowColorAndOpacity);
    
    UFUNCTION(BlueprintCallable)
    void SetOutlineColorAndOpacity(FLinearColor InOutlineColorAndOpacity);
    
    UFUNCTION(BlueprintCallable)
    void SetOutline(bool bInOutline);
    
    UFUNCTION(BlueprintCallable)
    void SetOpacity(float InOpacity);
    
    UFUNCTION(BlueprintCallable)
    void SetMinDesiredWidth(float InMinDesiredWidth);
    
    UFUNCTION(BlueprintCallable)
    void SetLeftAlignedCenter(bool bInLeftAlignedCenter);
    
    UFUNCTION(BlueprintCallable)
    void SetJustification(TEnumAsByte<ETextJustify::Type> InJustification);
    
    UFUNCTION(BlueprintCallable)
    void SetFont(UEndFont* InFont);
    
    UFUNCTION(BlueprintCallable)
    void SetColoredButtons(bool bInColoredButtons);
    
    UFUNCTION(BlueprintCallable)
    void SetColorAndOpacity(FSlateColor InColorAndOpacity);
    
    UFUNCTION(BlueprintCallable)
    void SetButtonLayoutMode(EEndMenuTextButtonLayoutMode InButtonLayoutMode);
    
    UFUNCTION(BlueprintCallable)
    void SetBottomOpacity(float InOpacity);
    
    UFUNCTION(BlueprintCallable)
    void SetBottomColorAndOpacity(FSlateColor InColorAndOpacity);
    
    UFUNCTION(BlueprintCallable)
    void SetBlendMode(TEnumAsByte<EBlendMode> InBlendMode);
    
    UFUNCTION(BlueprintCallable)
    void SetAutoWrapText(bool bInAutoWrapText);
    
    UFUNCTION(BlueprintCallable)
    void SetAutoUpdateButtons(bool bInAutoUpdateButtons);
    
    UFUNCTION(BlueprintCallable)
    void SetAutoShrinkText(bool bInAutoShrinkText);
    
    UFUNCTION(BlueprintCallable)
    void SetAllowMacro(bool bInAllowMacro);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FString GetText() const;
    
};

