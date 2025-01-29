#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndAssignStateChange.h"
#include "EndCommonInfo.h"
#include "EndObjectActor.h"
#include "EndObjectBase.h"
#include "EndObjectConnection.h"
#include "EndObjectEnemy.h"
#include "EndObjectKnot.h"
#include "EndObjectLayout.h"
#include "EndObjectNodeInfo.h"
#include "EndObjectParty.h"
#include "EndObjectTreasure.h"
#include "EndObject_StateChange.h"
#include "EndObject_StateTriggerData.h"
#include "StateObjectHandle.h"
#include "EndAssetEndObject.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndAssetEndObject : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Name;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint64, FEndObjectBase> Objects;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint64, FEndObjectActor> ObjectActors;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint64, FEndObjectEnemy> ObjectEnemies;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint64, FEndObjectParty> ObjectParties;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint64, FEndObjectTreasure> ObjectTreasures;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint64, FEndObjectLayout> ObjectLayouts;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint64, FEndObjectBase> ObjectsRef;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint64, FEndObjectBase> ObjectActorsRef;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint64, FEndObjectBase> ObjectEnemiesRef;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint64, FEndObjectBase> ObjectPartiesRef;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint64, FEndObjectBase> ObjectTreasuresRef;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint64, FEndObjectBase> ObjectLayoutsRef;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint64, FEndObjectNodeInfo> NodeInfos;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint64, FEndCommonInfo> CommonNodes;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FStateObjectHandle, FEndObject_StateChange> StateChanges;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FStateObjectHandle, FEndObject_StateTriggerData> StateTriggers;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FStateObjectHandle, FEndObject_StateChange> StateChangeRefs;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FStateObjectHandle, FEndCommonInfo> StateTriggerRefs;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FStateObjectHandle, FEndObjectKnot> Knots;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FStateObjectHandle, FEndAssignStateChange> AssignStateChanges;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FStateObjectHandle, FEndCommonInfo> StateCommonNodes;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndObjectConnection> Connections;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, uint64> TempActions;
    
    UEndAssetEndObject();

};

