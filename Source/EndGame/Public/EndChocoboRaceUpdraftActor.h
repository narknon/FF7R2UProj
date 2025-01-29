#pragma once
#include "CoreMinimal.h"
#include "EndChocoboRaceGimmickActorBase.h"
#include "EndChocoboRaceUpdraftActor.generated.h"

UCLASS(Blueprintable)
class AEndChocoboRaceUpdraftActor : public AEndChocoboRaceGimmickActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TargetHeight;
    
public:
    AEndChocoboRaceUpdraftActor(const FObjectInitializer& ObjectInitializer);

};

