#pragma once
#include "CoreMinimal.h"
#include "EndCharacterBase.h"
#include "EndModularCharacter.generated.h"

class UEndSkeletalMeshComponent;
class UEndSyncPoseSkeletalMeshComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndModularCharacter : public AEndCharacterBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSyncPoseSkeletalMeshComponent* TopsMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSyncPoseSkeletalMeshComponent* BottomsMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSyncPoseSkeletalMeshComponent* HairMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSyncPoseSkeletalMeshComponent* HaircovMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSyncPoseSkeletalMeshComponent* OptionalSyncPoseMesh0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSkeletalMeshComponent* OptionalAttachMesh0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName OptionalAttachSocketName0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSkeletalMeshComponent* OptionalAttachMesh1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName OptionalAttachSocketName1;
    
    AEndModularCharacter(const FObjectInitializer& ObjectInitializer);

};

