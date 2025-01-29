#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndBattleBreakableComponent.generated.h"

class AEndEnvironmentPhysicsStaticMeshActor;

UCLASS(Abstract, Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleBreakableComponent : public UActorComponent {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Export, meta=(AllowPrivateAccess=true))
    FName GroupId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Export, meta=(AllowPrivateAccess=true))
    bool bStartWithHidden;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Export, meta=(AllowPrivateAccess=true))
    FName BlockingVolumeLevelID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Export, meta=(AllowPrivateAccess=true))
    TArray<FName> BlockingVolumeIDList;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AEndEnvironmentPhysicsStaticMeshActor* OwnerActor;
    
public:
    UEndBattleBreakableComponent(const FObjectInitializer& ObjectInitializer);

};

