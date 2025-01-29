#pragma once
#include "CoreMinimal.h"
#include "Sound/SlateSound.h"
#include "EndSimpleMenu.h"
#include "Templates/SubclassOf.h"
#include "EndTestPlayTitleMenu.generated.h"

class UEndTrialOrderWindow;
class UEndUserWidget;
class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndTestPlayTitleMenu : public UEndSimpleMenu {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSlateSound DecideSound;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndUserWidget> OrderWindowWidgetClass;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UWidget* FocusedWidget;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndTrialOrderWindow* OrderWindow;
    
public:
    UEndTestPlayTitleMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnStartButtonClicked();
    
};

