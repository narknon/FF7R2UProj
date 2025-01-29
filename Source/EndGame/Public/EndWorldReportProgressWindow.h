#pragma once
#include "CoreMinimal.h"
#include "EndMapJournalMenuWindow.h"
#include "Templates/SubclassOf.h"
#include "EndWorldReportProgressWindow.generated.h"

class UEndWorldReportProgressPage;

UCLASS(Blueprintable, EditInlineNew)
class UEndWorldReportProgressWindow : public UEndMapJournalMenuWindow {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<TSubclassOf<UEndWorldReportProgressPage>> PageWidgetClasses;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    TArray<UEndWorldReportProgressPage*> PageWidgets;
    
public:
    UEndWorldReportProgressWindow();

};

