#pragma once
#include "CoreMinimal.h"
#include "EndChocoboPartsData.generated.h"

class USkeletalMesh;

USTRUCT(BlueprintType)
struct FEndChocoboPartsData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USkeletalMesh* PartsMesh_Head;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USkeletalMesh* PartsMesh_Body;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USkeletalMesh* PartsMesh_Legs;
    
    ENDGAME_API FEndChocoboPartsData();
};

