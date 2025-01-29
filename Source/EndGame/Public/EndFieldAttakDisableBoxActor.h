#pragma once
#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EndFieldAttakDisableBoxActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndFieldAttakDisableBoxActor : public ATriggerBox {
    GENERATED_BODY()
public:
    AEndFieldAttakDisableBoxActor(const FObjectInitializer& ObjectInitializer);

};

