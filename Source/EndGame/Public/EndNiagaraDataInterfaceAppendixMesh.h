#pragma once
#include "CoreMinimal.h"
#include "NiagaraDataInterface.h"
#include "EEndAnimNotifyAttachType.h"
#include "EndNiagaraDataInterfaceAppendixMesh.generated.h"

class UEffectAppendixMesh;

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndNiagaraDataInterfaceAppendixMesh : public UNiagaraDataInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> m_FilteredBones;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> m_FilteredSockets;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEffectAppendixMesh* m_EffectAppendixMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_bReferencesGPUSkin: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_bReferencesGPUBone: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_bReferencesWheel: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_bReferencesFeelerTornade: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_BindComponentName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAnimNotifyAttachType m_BindAttachType;
    
    UEndNiagaraDataInterfaceAppendixMesh();

};

