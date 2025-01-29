#pragma once
#include "CoreMinimal.h"
#include "EndMassiveEnvironmentRenderData.generated.h"

USTRUCT(BlueprintType)
struct FEndMassiveEnvironmentRenderData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint8> RequestedMeshMipIndices;
    
    ENDGAME_API FEndMassiveEnvironmentRenderData();
};

