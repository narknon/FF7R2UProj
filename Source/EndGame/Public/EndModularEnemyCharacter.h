#pragma once
#include "CoreMinimal.h"
#include "EndCharacter.h"
#include "EndModularEnemyCharacter.generated.h"

class UEndSyncPoseSkeletalMeshComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndModularEnemyCharacter : public AEndCharacter {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSyncPoseSkeletalMeshComponent* BodyMesh;
    
    AEndModularEnemyCharacter(const FObjectInitializer& ObjectInitializer);

};

