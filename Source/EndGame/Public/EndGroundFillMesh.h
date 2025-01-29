#pragma once
#include "CoreMinimal.h"
#include "EndGroundFillMesh.generated.h"

class UStaticMesh;

USTRUCT(BlueprintType)
struct FEndGroundFillMesh {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FillRateLimit;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float GradientLimit;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UStaticMesh* StaticMesh;
    
    ENDGAME_API FEndGroundFillMesh();
};

