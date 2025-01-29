#pragma once
#include "CoreMinimal.h"
#include "EndBattleDamageSourceComponent.h"
#include "EndBattleDamageSourceComponentDisk.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceComponentDisk : public UEndBattleDamageSourceComponent {
    GENERATED_BODY()
public:
    UEndBattleDamageSourceComponentDisk(const FObjectInitializer& ObjectInitializer);

};

