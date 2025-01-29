#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldActionStateManagedActor.h"
#include "EndFieldMonkeyBarEntryPoint.h"
#include "EndFieldMonkeyBarGameInfo.h"
#include "EndFieldActionActorMonkeyBars.generated.h"

class ASkeletalMeshActor;
class AStaticMeshActor;
class UEndFieldActionTriggerComponent;

UCLASS(Blueprintable)
class AEndFieldActionActorMonkeyBars : public AEndFieldActionStateManagedActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* TickableVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AStaticMeshActor* BarStaticMeshActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ASkeletalMeshActor* BarSkeletalMeshActor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldMonkeyBarEntryPoint> EntryPoints;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldMonkeyBarGameInfo> BarGameArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform BarCreateBaseTrans;
    
    AEndFieldActionActorMonkeyBars(const FObjectInitializer& ObjectInitializer);

};

