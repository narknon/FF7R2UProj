#pragma once
#include "CoreMinimal.h"
#include "EVfxNonUniformKind.h"
#include "VfxNonUniformRandom.generated.h"

USTRUCT(BlueprintType)
struct FVfxNonUniformRandom {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EVfxNonUniformKind m_Kind;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_Param;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_bReverse: 1;
    
    ENDGAME_API FVfxNonUniformRandom();
};

