#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Styling/SlateTypes.h"
#include "Types/SlateEnums.h"
#include "Types/SlateEnums.h"
#include "Types/SlateEnums.h"
#include "Sound/SlateSound.h"
#include "Components/ContentWidget.h"
#include "Components/Button.h"
#include "Components/Button.h"
#include "Components/Button.h"
#include "Components/Button.h"
#include "EndButton.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndButton : public UContentWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FButtonStyle WidgetStyle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor ColorAndOpacity;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor BackgroundColor;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EButtonClickMethod::Type> ClickMethod;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EButtonTouchMethod::Type> TouchMethod;
    
    UPROPERTY(AdvancedDisplay, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EButtonPressMethod::Type> PressMethod;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool IsFocusable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool IsForceHovered;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool CanPress;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool IgnoreKeyRepeat;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool FakeDisabled;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString HelpText;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString GuideText;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSlateSound ErrorSlateSound;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOnButtonClickedEvent OnClicked;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOnButtonPressedEvent OnPressed;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOnButtonReleasedEvent OnReleased;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOnButtonHoverEvent OnHovered;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOnButtonHoverEvent OnUnhovered;
    
    UEndButton();

    UFUNCTION(BlueprintCallable)
    void SetTouchMethod(TEnumAsByte<EButtonTouchMethod::Type> InTouchMethod);
    
    UFUNCTION(BlueprintCallable)
    void SetStyle(const FButtonStyle& InStyle);
    
    UFUNCTION(BlueprintCallable)
    void SetPressMethod(TEnumAsByte<EButtonPressMethod::Type> InPressMethod);
    
    UFUNCTION(BlueprintCallable)
    void SetIsFocusable(bool bInIsFocusable);
    
    UFUNCTION(BlueprintCallable)
    void SetIgnoreKeyRepeat(bool bInIgnoreKeyRepeat);
    
    UFUNCTION(BlueprintCallable)
    void SetHelpText(const FString& InText);
    
    UFUNCTION(BlueprintCallable)
    void SetGuideText(const FString& InText);
    
    UFUNCTION(BlueprintCallable)
    void SetForceHovered(bool bInHovered);
    
    UFUNCTION(BlueprintCallable)
    void SetFakeDisabled(bool bInFakeDisabled);
    
    UFUNCTION(BlueprintCallable)
    void SetColorAndOpacity(FLinearColor InColorAndOpacity);
    
    UFUNCTION(BlueprintCallable)
    void SetClickMethod(TEnumAsByte<EButtonClickMethod::Type> InClickMethod);
    
    UFUNCTION(BlueprintCallable)
    void SetCanPress(bool bInCanPress);
    
    UFUNCTION(BlueprintCallable)
    void SetBackgroundColor(FLinearColor InBackgroundColor);
    
    UFUNCTION(BlueprintCallable)
    void Release();
    
    UFUNCTION(BlueprintCallable)
    void Press();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsPressed() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsFakeDisabled() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool GetIsForceHovered() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool GetIsFocusable() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool GetIgnoreKeyRepeat() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool GetCanPress() const;
    
};

