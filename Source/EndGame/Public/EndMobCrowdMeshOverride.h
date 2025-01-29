#pragma once
#include "CoreMinimal.h"
#include "EndMobCrowdMeshOverride.generated.h"

class UAnimSequenceBase;
class USkeletalMesh;
class UStaticMesh;

USTRUCT(BlueprintType)
struct FEndMobCrowdMeshOverride {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UAnimSequenceBase* AnimSequence;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USkeletalMesh* AttachMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AttachSocketName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UStaticMesh* StaticMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bForceCastShadow;
    
    ENDGAME_API FEndMobCrowdMeshOverride();
};

