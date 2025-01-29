#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCinemaButton.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndCinemaButton : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SkipWaitTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MenuWaitTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MenuOutTime;
    
    UEndCinemaButton();

};

