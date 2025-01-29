#pragma once
#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "EndEffectAttachInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndEffectAttachInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAttachmentRule m_LocationRule;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAttachmentRule m_RotationRule;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAttachmentRule m_ScaleRule;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_bInWeldSimulatedBodies: 1;
    
    ENDGAME_API FEndEffectAttachInfo();
};

