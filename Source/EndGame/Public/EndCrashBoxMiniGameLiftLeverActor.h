#pragma once
#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "EndCrashBoxMiniGameLiftLeverActor.generated.h"

class AEndCrashBoxMiniGameLiftRootActor;
class UStaticMeshComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndCrashBoxMiniGameLiftLeverActor : public AStaticMeshActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_GroupIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UStaticMeshComponent* m_StaticMeshComponent;
    
public:
    AEndCrashBoxMiniGameLiftLeverActor(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetLiftRootActor(AEndCrashBoxMiniGameLiftRootActor* LiftRootActor);
    
};

