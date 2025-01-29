#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMainMenu.generated.h"

class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndMainMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndTextBlock* TitleText;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndTextBlock* TimeText;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndTextBlock* GilText;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndTextBlock* HelpText;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndTextBlock* GuideText;
    
public:
    UEndMainMenu();

};

