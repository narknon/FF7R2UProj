#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndEnemyReportBtn.generated.h"

class UEndButton;

UCLASS(Blueprintable, EditInlineNew)
class UEndEnemyReportBtn : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndButton* SelectBtn;
    
    UEndEnemyReportBtn();

};

