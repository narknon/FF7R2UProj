#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "EndSkeletalMeshActor.h"
#include "EndChickenLureMiniGameSkeletalCanActor.generated.h"

class AActor;
class AEndEnvironmentSkeletalMeshActor;
class UPrimitiveComponent;
class USkeletalMeshComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndChickenLureMiniGameSkeletalCanActor : public AEndSkeletalMeshActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USkeletalMeshComponent* m_SkeletalMeshComponent;
    
public:
    AEndChickenLureMiniGameSkeletalCanActor(const FObjectInitializer& ObjectInitializer);

private:
    UFUNCTION(BlueprintCallable)
    void SetRopeLootActor(AEndEnvironmentSkeletalMeshActor* RopeLootActor);
    
    UFUNCTION(BlueprintCallable)
    void SetReferenceSkeletalMesh(USkeletalMeshComponent* SkeletalMeshComp);
    
    UFUNCTION(BlueprintCallable)
    void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
};

