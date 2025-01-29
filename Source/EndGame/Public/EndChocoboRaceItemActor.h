#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboRaceItemType.h"
#include "EndChocoboRaceGimmickActorBase.h"
#include "Templates/SubclassOf.h"
#include "EndChocoboRaceItemActor.generated.h"

class AEndSkeletalMeshActor;
class UObject;

UCLASS(Blueprintable)
class AEndChocoboRaceItemActor : public AEndChocoboRaceGimmickActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndChocoboRaceItemType ItemType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UObject*> AssetUserData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndSkeletalMeshActor> ItemClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RespawnIntervalByPlayer;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RespawnIntervalByNpc;
    
public:
    AEndChocoboRaceItemActor(const FObjectInitializer& ObjectInitializer);

};

