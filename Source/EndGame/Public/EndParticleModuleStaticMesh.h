#pragma once
#include "CoreMinimal.h"
#include "Particles/Location/ParticleModuleLocationBase.h"
#include "EEndEffectStaticMeshSelectKind.h"
#include "EndParticleModuleStaticMesh.generated.h"

class UStaticMesh;

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndParticleModuleStaticMesh : public UParticleModuleLocationBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UStaticMesh* m_StaticMesh;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndEffectStaticMeshSelectKind m_SelectKind;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 m_OrderOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_OrderReverse: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_bMultiplySurfaceArea: 1;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint16> m_UserSetVertexIndexArray;
    
    UEndParticleModuleStaticMesh();

};

