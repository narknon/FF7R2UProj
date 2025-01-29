#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndCrashBoxMiniGameActorManager.generated.h"

class AStaticMeshActor;

UCLASS(Blueprintable)
class ENDGAME_API AEndCrashBoxMiniGameActorManager : public AActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<AStaticMeshActor*> m_HideNormalActors;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<AStaticMeshActor*> m_HideHardActors;
    
public:
    AEndCrashBoxMiniGameActorManager(const FObjectInitializer& ObjectInitializer);

};

