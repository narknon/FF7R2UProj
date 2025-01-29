#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndNewSenseRight.generated.h"

class UEndNewSenseDetailAbility;
class UEndNewSenseDetailBpReinforce;
class UEndNewSenseDetailLog;
class UEndNewSenseDetailResistances;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndNewSenseRight : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNewSenseDetailResistances* Resistances;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNewSenseDetailBpReinforce* BpReinforce;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNewSenseDetailLog* Log;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNewSenseDetailAbility* Ability;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Btn_R;
    
    UEndNewSenseRight();

};

