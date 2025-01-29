#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboRaceBombSearchType.h"
#include "EndTriggerBox.h"
#include "EndChocoboRaceBombSearchTriggerBox.generated.h"

class AEndChocoboRaceBombBalloonActor;

UCLASS(Blueprintable)
class AEndChocoboRaceBombSearchTriggerBox : public AEndTriggerBox {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<AEndChocoboRaceBombBalloonActor> BombActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BombActorName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndChocoboRaceBombSearchType SearchType;
    
public:
    AEndChocoboRaceBombSearchTriggerBox(const FObjectInitializer& ObjectInitializer);

};

