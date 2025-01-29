#pragma once
#include "CoreMinimal.h"
#include "EndMobCrowdAttachment.generated.h"

class UStaticMesh;

USTRUCT(BlueprintType)
struct FEndMobCrowdAttachment {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UStaticMesh* AttachMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AttachSocketName;
    
    ENDGAME_API FEndMobCrowdAttachment();
};

