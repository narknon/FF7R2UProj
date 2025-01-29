#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndEquipInfoDetailAccessory.generated.h"

class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndEquipInfoDetailAccessory : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_AccessoryInfo;
    
    UEndEquipInfoDetailAccessory();

};

