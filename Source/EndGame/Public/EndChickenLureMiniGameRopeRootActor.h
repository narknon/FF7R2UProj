#pragma once
#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Templates/SubclassOf.h"
#include "EndChickenLureMiniGameRopeRootActor.generated.h"

class AActor;
class AEndChickenLureMiniGameSkeletalCanActor;
class AEndSkeletalMeshActor;
class USkeletalMeshComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndChickenLureMiniGameRopeRootActor : public AStaticMeshActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndSkeletalMeshActor> RopeClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndChickenLureMiniGameSkeletalCanActor> SkeletalCanClass;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USkeletalMeshComponent* m_RopeSkeletalMeshComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USkeletalMeshComponent* m_CanSkeletalMeshComponent;
    
public:
    AEndChickenLureMiniGameRopeRootActor(const FObjectInitializer& ObjectInitializer);

private:
    UFUNCTION(BlueprintCallable)
    void SetSkeletalCanActor(AEndChickenLureMiniGameSkeletalCanActor* CanActor);
    
    UFUNCTION(BlueprintCallable)
    void SetRopeActor(AActor* RopeActor);
    
    UFUNCTION(BlueprintCallable)
    void SetReferenceSkeletalCanStaticMesh(USkeletalMeshComponent* SkeletalMeshComp);
    
};

