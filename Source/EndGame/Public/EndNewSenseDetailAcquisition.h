#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndNewSenseDetailAcquisition.generated.h"

class UEndListBox;
class UEndNewSenseTitleCell;

UCLASS(Blueprintable, EditInlineNew)
class UEndNewSenseDetailAcquisition : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNewSenseTitleCell* Title_Acquisition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndListBox* List_Acquisition;
    
    UEndNewSenseDetailAcquisition();

};

