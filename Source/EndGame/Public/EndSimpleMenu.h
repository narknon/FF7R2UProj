#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndSimpleMenu.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndSimpleMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bResident;
    
    UEndSimpleMenu();

};

