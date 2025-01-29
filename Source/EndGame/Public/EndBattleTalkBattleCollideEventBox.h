#pragma once
#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EndBattleTalkBattleCollideEventBox.generated.h"

UCLASS(Blueprintable)
class AEndBattleTalkBattleCollideEventBox : public ATriggerBox {
    GENERATED_BODY()
public:
    AEndBattleTalkBattleCollideEventBox(const FObjectInitializer& ObjectInitializer);

};

