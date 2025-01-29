#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndSkeletalMeshActorAnimInstance.h"
#include "EndRopeAnimInstance.generated.h"

class AActor;

UCLASS(Blueprintable, NonTransient)
class UEndRopeAnimInstance : public UEndSkeletalMeshActorAnimInstance {
    GENERATED_BODY()
public:
    UEndRopeAnimInstance();

    UFUNCTION(BlueprintCallable)
    bool UnregisterAttachPoint(int32 AttachPointHandle);
    
    UFUNCTION(BlueprintCallable)
    void SetRopeDistanceBias(float InDistanceBias);
    
    UFUNCTION(BlueprintCallable)
    void SetOverrideRopeLength(float InRopeLength);
    
    UFUNCTION(BlueprintCallable)
    void SetFixedRoot(bool bFixed);
    
    UFUNCTION(BlueprintCallable)
    void SetAttachPointLocation(int32 AttachPointHandle, FVector Location);
    
    UFUNCTION(BlueprintCallable)
    void RemoveRopeContactIgnoreActor(AActor* Actor);
    
    UFUNCTION(BlueprintCallable)
    int32 RegisterAttachPoint(float Distance);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsAppearedRope() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetTotalParticleLength() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetRootPullVector2D() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetRootPullVector() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetRootPullLocation() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetRootPullLimitLength2D() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetRootPullLimitLength() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetRootLocation() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetEndPullVector2D() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetEndPullVector() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetEndPullLocation() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetEndPullLimitLength2D() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetEndPullLimitLength() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetEndLocation() const;
    
    UFUNCTION(BlueprintCallable)
    void DetachEndPoint();
    
    UFUNCTION(BlueprintCallable)
    void AttachEndPoint(FVector EndPointLocation, const FVector& EndPointVector);
    
    UFUNCTION(BlueprintCallable)
    void AddRopeContactIgnoreActor(AActor* Actor);
    
};

