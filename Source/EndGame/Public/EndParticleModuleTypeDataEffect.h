#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Particles/TypeData/ParticleModuleTypeDataBase.h"
#include "EndEffectAttachInfo.h"
#include "EndParticleModuleTypeDataEffect.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndParticleModuleTypeDataEffect : public UParticleModuleTypeDataBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSoftObjectPath m_CreateEffectPath;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_bAttachment: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndEffectAttachInfo m_AttachInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_bSyncParticle: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_bApplyRotation: 1;
    
    UEndParticleModuleTypeDataEffect();

};

