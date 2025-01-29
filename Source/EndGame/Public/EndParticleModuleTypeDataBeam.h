#pragma once
#include "CoreMinimal.h"
#include "Particles/TypeData/ParticleModuleTypeDataBeam2.h"
#include "Distributions/DistributionVector.h"
#include "EndParticleModuleTypeDataBeam.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndParticleModuleTypeDataBeam : public UParticleModuleTypeDataBeam2 {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionVector m_RandomUV;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionVector m_RandomUVSpeed;
    
    UEndParticleModuleTypeDataBeam();

};

