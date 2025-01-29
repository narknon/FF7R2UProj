#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndUserWidget.h"
#include "EndCmdShortcutCell.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndCmdShortcutCell : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor _UnlimitedMPCostColor;
    
    UEndCmdShortcutCell();

};

