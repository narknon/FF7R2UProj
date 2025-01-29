#pragma once
#include "CoreMinimal.h"
#include "EndSkeletalMeshActor.h"
#include "EndWeaponSkeletalMeshActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndWeaponSkeletalMeshActor : public AEndSkeletalMeshActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> PlayAnimationNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEndAnimationLooping;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 MateriaMaterialIndex;
    
    AEndWeaponSkeletalMeshActor(const FObjectInitializer& ObjectInitializer);

};

