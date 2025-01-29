#pragma once
#include "CoreMinimal.h"
#include "Particles/TypeData/ParticleModuleTypeDataBase.h"
#include "EndParticleModuleTypeDataEmitter.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndParticleModuleTypeDataEmitter : public UParticleModuleTypeDataBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_SourceEmitterName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_DisableSourceEmitterInstance: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_SpawnWorldSpace: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_bSyncParticle: 1;
    
    UEndParticleModuleTypeDataEmitter();

};

