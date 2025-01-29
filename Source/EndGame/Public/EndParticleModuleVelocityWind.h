#pragma once
#include "CoreMinimal.h"
#include "Distributions/DistributionFloat.h"
#include "EndParticleModuleBase.h"
#include "EndParticleModuleVelocityWind.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndParticleModuleVelocityWind : public UEndParticleModuleBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionFloat m_WindScale;
    
    UEndParticleModuleVelocityWind();

};

