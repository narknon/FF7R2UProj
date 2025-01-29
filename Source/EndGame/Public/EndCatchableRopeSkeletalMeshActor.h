#pragma once
#include "CoreMinimal.h"
#include "EndSkeletalMeshActor.h"
#include "EndCatchableRopeSkeletalMeshActor.generated.h"

class AStaticMeshActor;

UCLASS(Blueprintable)
class ENDGAME_API AEndCatchableRopeSkeletalMeshActor : public AEndSkeletalMeshActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RopeLength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AStaticMeshActor* PullActorPtr;
    
    AEndCatchableRopeSkeletalMeshActor(const FObjectInitializer& ObjectInitializer);

};

