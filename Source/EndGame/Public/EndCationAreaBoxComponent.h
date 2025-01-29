#pragma once
#include "CoreMinimal.h"
#include "EndBattleAreaBoxComponentBase.h"
#include "EndCationAreaBoxComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndCationAreaBoxComponent : public UEndBattleAreaBoxComponentBase {
    GENERATED_BODY()
public:
    UEndCationAreaBoxComponent(const FObjectInitializer& ObjectInitializer);

};

