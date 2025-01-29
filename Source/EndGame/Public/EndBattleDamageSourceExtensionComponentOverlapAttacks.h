#pragma once
#include "CoreMinimal.h"
#include "EndBattleDamageSourceExtensionComponent.h"
#include "EndBattleDamageSourceExtensionComponentOverlapAttacks.generated.h"

class UEndBattleDamageSourceComponentTraceHit;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceExtensionComponentOverlapAttacks : public UEndBattleDamageSourceExtensionComponent {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBattleDamageSourceComponentTraceHit* SimultaneousDelayEnemyComponent;
    
public:
    UEndBattleDamageSourceExtensionComponentOverlapAttacks(const FObjectInitializer& ObjectInitializer);

};

