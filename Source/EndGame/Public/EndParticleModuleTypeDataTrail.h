#pragma once
#include "CoreMinimal.h"
#include "Particles/TypeData/ParticleModuleTypeDataAnimTrail.h"
#include "Distributions/DistributionFloat.h"
#include "Distributions/DistributionVector.h"
#include "EndParticleModuleTypeDataTrail.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndParticleModuleTypeDataTrail : public UParticleModuleTypeDataAnimTrail {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionVector m_PointA;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionVector m_PointB;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionFloat m_TrailWidth;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint16 m_MaxParticle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_EnableFlipV: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_SocketNameA;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_SocketNameB;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_RefPointNameA;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_RefPointNameB;
    
    UEndParticleModuleTypeDataTrail();

};

