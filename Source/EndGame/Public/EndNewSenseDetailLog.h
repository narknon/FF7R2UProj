#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndNewSenseDetailLog.generated.h"

class UEndListBox;
class UEndNewSenseTitleCell;

UCLASS(Blueprintable, EditInlineNew)
class UEndNewSenseDetailLog : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNewSenseTitleCell* Title_Log;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndListBox* List_Log;
    
    UEndNewSenseDetailLog();

};

