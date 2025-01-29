#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "Engine/StaticMeshActor.h"
#include "EndChickenLureMiniGameCanActor.generated.h"

class AActor;
class AEndEnvironmentSkeletalMeshActor;
class UPrimitiveComponent;
class UStaticMeshComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndChickenLureMiniGameCanActor : public AStaticMeshActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UStaticMeshComponent* m_StaticMeshComponent;
    
public:
    AEndChickenLureMiniGameCanActor(const FObjectInitializer& ObjectInitializer);

private:
    UFUNCTION(BlueprintCallable)
    void SetRopeLootActor(AEndEnvironmentSkeletalMeshActor* RopeLootActor);
    
    UFUNCTION(BlueprintCallable)
    void SetReferenceStaticMesh(UStaticMeshComponent* StaticMeshComp);
    
    UFUNCTION(BlueprintCallable)
    void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
};

