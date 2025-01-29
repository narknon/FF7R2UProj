#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndBattleAreaBoxComponentBase.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleAreaBoxComponentBase : public UBoxComponent {
    GENERATED_BODY()
public:
    UEndBattleAreaBoxComponentBase(const FObjectInitializer& ObjectInitializer);

};

