#pragma once
#include "CoreMinimal.h"
#include "Distributions/DistributionFloat.h"
#include "EndParticleModuleBase.h"
#include "VfxParticleModuleActorDithreFade.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UVfxParticleModuleActorDithreFade : public UEndParticleModuleBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionFloat m_BlendScale;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionFloat m_BlendAdd;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> m_MaterialSlotNames;
    
    UVfxParticleModuleActorDithreFade();

};

