#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndNewSenseDetailBpReinforce.generated.h"

class UEndListBox;
class UEndNewSenseTitleCell;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndNewSenseDetailBpReinforce : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNewSenseTitleCell* Title_Resistances;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndListBox* List_BpReinforce;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_None;
    
    UEndNewSenseDetailBpReinforce();

};

