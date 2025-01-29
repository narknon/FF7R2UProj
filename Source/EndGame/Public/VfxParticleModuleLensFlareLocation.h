#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Particles/Location/ParticleModuleLocationBase.h"
#include "VfxLensFlareObjectData.h"
#include "VfxParticleModuleLensFlareLocation.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UVfxParticleModuleLensFlareLocation : public UParticleModuleLocationBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D m_vCenterOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_fCentralMagnificationArea;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_fCentralMagnificationCurvedStartDirection;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_fCentralMagnificationCurvedEndDirection;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FVfxLensFlareObjectData> m_ObjectDataList;
    
    UVfxParticleModuleLensFlareLocation();

};

