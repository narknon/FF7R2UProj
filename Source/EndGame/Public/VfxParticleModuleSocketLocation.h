#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Particles/Location/ParticleModuleLocationBase.h"
#include "Distributions/DistributionFloat.h"
#include "VfxParticleModuleSocketLocation.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UVfxParticleModuleSocketLocation : public UParticleModuleLocationBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_WildcardSocketName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> m_SocketNameArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector m_VelocityDir;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRawDistributionFloat m_VelocityScale;
    
    UVfxParticleModuleSocketLocation();

};

