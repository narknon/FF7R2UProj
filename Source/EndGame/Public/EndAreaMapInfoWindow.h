#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndAreaMapInfoWindow.generated.h"

class UWidgetAnimation;

UCLASS(Blueprintable, EditInlineNew)
class UEndAreaMapInfoWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UWidgetAnimation* MenuInAnimation;
    
public:
    UEndAreaMapInfoWindow();

};

