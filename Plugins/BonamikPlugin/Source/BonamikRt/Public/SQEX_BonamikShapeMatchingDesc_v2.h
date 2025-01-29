#pragma once
#include "CoreMinimal.h"
#include "SQEX_BonamikShapeMatchingDesc_v2.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_BonamikShapeMatchingDesc_v2 {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_TotalParticle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_RegionSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_Stiffness;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 m_ParticleIds[50];
    
    BONAMIKRT_API FSQEX_BonamikShapeMatchingDesc_v2();
};

