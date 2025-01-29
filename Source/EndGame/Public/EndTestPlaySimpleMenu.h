#pragma once
#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "Sound/SlateSound.h"
#include "EndSimpleMenu.h"
#include "EndTestPlaySimpleMenu.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndTestPlaySimpleMenu : public UEndSimpleMenu {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FKey DecideKey;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSlateSound DecideSound;
    
    UEndTestPlaySimpleMenu();

};

