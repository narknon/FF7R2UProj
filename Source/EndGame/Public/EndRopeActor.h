#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EndRopeAutoConstraint.h"
#include "EndSkeletalMeshActor.h"
#include "EndRopeActor.generated.h"

class AActor;
class USkeletalMeshComponent;

UCLASS(Blueprintable)
class AEndRopeActor : public AEndSkeletalMeshActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnabledPhysicsCollision;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndRopeAutoConstraint> AutoConstraintOnAttach;
    
    AEndRopeActor(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void RemoveRopeContactIgnoreActor(AActor* Actor);
    
    UFUNCTION(BlueprintCallable)
    void DetachRopeRoot();
    
    UFUNCTION(BlueprintCallable)
    void DetachRopeEndPoint();
    
    UFUNCTION(BlueprintCallable)
    void AttachRopeRootToTransform(const FTransform& Transform);
    
    UFUNCTION(BlueprintCallable)
    void AttachRopeRootToSkeletamMesh(USkeletalMeshComponent* Mesh, FName SocketName);
    
    UFUNCTION(BlueprintCallable)
    void AttachRopeRootToActor(AActor* Actor, FName SocketName);
    
    UFUNCTION(BlueprintCallable)
    void AttachRopeEndPointToSkeletalMesh(USkeletalMeshComponent* Mesh, FName SocketName);
    
    UFUNCTION(BlueprintCallable)
    void AttachRopeEndPointToLocation(const FVector& Location);
    
    UFUNCTION(BlueprintCallable)
    void AttachRopeEndPointToActor(AActor* Actor, FName SocketName);
    
    UFUNCTION(BlueprintCallable)
    void AddRopeContactIgnoreActor(AActor* Actor);
    
};

