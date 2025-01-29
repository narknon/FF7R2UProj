#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndBattleSettingInfo.generated.h"

class UEndListBox;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndBattleSettingInfo : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_TypeTitle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndListBox* InfoList;
    
    UEndBattleSettingInfo();

};

