#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndEquipInfoDetailAbility.generated.h"

class UEndAbilityName2;
class UEndBillboard;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndEquipInfoDetailAbility : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndAbilityName2* AbilityName2;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_AbilityInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Info;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBillboard* MovieBillboard;
    
    UEndEquipInfoDetailAbility();

};

