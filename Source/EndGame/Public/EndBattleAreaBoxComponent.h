#pragma once
#include "CoreMinimal.h"
#include "EndBattleAreaBoxComponentBase.h"
#include "EndBattleAreaBoxComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleAreaBoxComponent : public UEndBattleAreaBoxComponentBase {
    GENERATED_BODY()
public:
    UEndBattleAreaBoxComponent(const FObjectInitializer& ObjectInitializer);

};

