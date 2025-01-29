#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndNewSenseDetailResistances.generated.h"

class UEndListBox;
class UEndNewSenseTitleCell;

UCLASS(Blueprintable, EditInlineNew)
class UEndNewSenseDetailResistances : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNewSenseTitleCell* Title_Resistances;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndListBox* List_Resistances;
    
    UEndNewSenseDetailResistances();

};

