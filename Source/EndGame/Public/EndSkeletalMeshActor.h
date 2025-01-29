#pragma once
#include "CoreMinimal.h"
#include "EndAnimSetActorInterface.h"
#include "EndRagdollSEData.h"
#include "EndSkeletalMeshActorBase.h"
#include "EndSkeletalMeshActor.generated.h"

class UActorComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndSkeletalMeshActor : public AEndSkeletalMeshActorBase, public IEndAnimSetActorInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TMap<FName, UActorComponent*> ComponentTable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnablePhysicsAssetCollision;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndRagdollSEData> RagdollSEData;
    
    AEndSkeletalMeshActor(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

