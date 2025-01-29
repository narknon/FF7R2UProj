#pragma once
#include "CoreMinimal.h"
#include "EndNaviMapMetaDataVertex.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndNaviMapMetaDataVertex {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float X;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Y;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Z;
    
    FEndNaviMapMetaDataVertex();
};

