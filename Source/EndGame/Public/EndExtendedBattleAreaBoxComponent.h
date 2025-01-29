#pragma once
#include "CoreMinimal.h"
#include "EndBattleAreaBoxComponentBase.h"
#include "EndExtendedBattleAreaBoxComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndExtendedBattleAreaBoxComponent : public UEndBattleAreaBoxComponentBase {
    GENERATED_BODY()
public:
    UEndExtendedBattleAreaBoxComponent(const FObjectInitializer& ObjectInitializer);

};

