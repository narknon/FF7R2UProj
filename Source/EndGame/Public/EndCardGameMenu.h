#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCardGameMenu.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndCardGameMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UClass* _PassClass;
    
public:
    UEndCardGameMenu();

    UFUNCTION(BlueprintCallable)
    void OnYesButtonPressed();
    
    UFUNCTION(BlueprintCallable)
    void OnNoButtonPressed();
    
};

