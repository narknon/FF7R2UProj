#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndLocationTitle.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndLocationTitle : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LoopTime;
    
    UEndLocationTitle();

};

