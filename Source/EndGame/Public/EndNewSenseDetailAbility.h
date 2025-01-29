#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndNewSenseDetailAbility.generated.h"

class UEndListBox;
class UEndNewSenseTitleCell;

UCLASS(Blueprintable, EditInlineNew)
class UEndNewSenseDetailAbility : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNewSenseTitleCell* Title_Ability;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndListBox* List_Ability_00;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndListBox* List_Ability_01;
    
    UEndNewSenseDetailAbility();

};

