#pragma once
#include "CoreMinimal.h"
#include "EndMainMenuWindow.h"
#include "EndMainDlcBtnMenu.generated.h"

class UEndButton;
class UEndImage;
class UEndImageSet;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndMainDlcBtnMenu : public UEndMainMenuWindow {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndButton* SelectBtn;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Category;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImageSet* Icon_Clear;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* EndTextBlock_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_ReportTitle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImage* Icon_New;
    
    UEndMainDlcBtnMenu();

};

