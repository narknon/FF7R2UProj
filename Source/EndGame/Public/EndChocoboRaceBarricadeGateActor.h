#pragma once
#include "CoreMinimal.h"
#include "EndChocoboRaceGimmickActorBase.h"
#include "Templates/SubclassOf.h"
#include "EndChocoboRaceBarricadeGateActor.generated.h"

class AEndEnvironmentSkeletalMeshActor;

UCLASS(Blueprintable)
class AEndChocoboRaceBarricadeGateActor : public AEndChocoboRaceGimmickActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndEnvironmentSkeletalMeshActor> GateClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bOpenStart;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OpenTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float CloseTime;
    
public:
    AEndChocoboRaceBarricadeGateActor(const FObjectInitializer& ObjectInitializer);

};

