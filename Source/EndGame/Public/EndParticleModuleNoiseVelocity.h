#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Distributions/DistributionVector.h"
#include "EndParticleModuleBase.h"
#include "EndParticleModuleNoiseVelocity.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndParticleModuleNoiseVelocity : public UEndParticleModuleBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector4 m_FrequencyModulationX;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector4 m_FrequencyModulationY;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector4 m_FrequencyModulationZ;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionVector m_CycleTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionVector m_Amplitude;
    
    UEndParticleModuleNoiseVelocity();

};

