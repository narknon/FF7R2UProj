#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndWorldReportProgressPage.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndWorldReportProgressPage : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Title;
    
    UEndWorldReportProgressPage();

};

