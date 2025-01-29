#pragma once
#include "CoreMinimal.h"
#include "EndSwitchableSkeletalMeshPair.generated.h"

class USkeletalMesh;

USTRUCT(BlueprintType)
struct FEndSwitchableSkeletalMeshPair {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Label;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USkeletalMesh* Mesh;
    
    ENDGAME_API FEndSwitchableSkeletalMeshPair();
};

