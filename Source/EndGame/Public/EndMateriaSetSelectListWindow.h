#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMateriaSetSelectListWindow.generated.h"

class UEndTextBlock;
class UEndVirtualScrollBox;

UCLASS(Blueprintable, EditInlineNew)
class UEndMateriaSetSelectListWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Title;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* EndVirtualScrollBox_88;
    
    UEndMateriaSetSelectListWindow();

};

