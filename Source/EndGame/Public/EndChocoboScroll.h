#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndChocoboScroll.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndChocoboScroll : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StartAtTime;
    
    UEndChocoboScroll();

};

