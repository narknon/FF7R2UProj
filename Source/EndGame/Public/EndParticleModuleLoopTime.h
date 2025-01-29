#pragma once
#include "CoreMinimal.h"
#include "EndParticleModuleBase.h"
#include "EndParticleModuleLoopTime.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndParticleModuleLoopTime : public UEndParticleModuleBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_fBeginLoop;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_fEndLoop;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_PerParticleLoop: 1;
    
    UEndParticleModuleLoopTime();

};

