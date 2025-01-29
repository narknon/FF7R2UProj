#pragma once
#include "CoreMinimal.h"
#include "EndSimpleMenu.h"
#include "Templates/SubclassOf.h"
#include "EndTitleMenu.generated.h"

class UUserWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndTitleMenu : public UEndSimpleMenu {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UUserWidget> StartMenuWidgetClass;
    
    UEndTitleMenu();

private:
    UFUNCTION(BlueprintCallable)
    void OnStartMenuEnd();
    
    UFUNCTION(BlueprintCallable)
    void OnPressedAnyButton();
    
};

