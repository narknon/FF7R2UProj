#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NiagaraDataInterface.h"
#include "VfxLensFlareObjectData.h"
#include "EndNiagaraDataInterfaceLensFlare.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndNiagaraDataInterfaceLensFlare : public UNiagaraDataInterface {
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
    
    UEndNiagaraDataInterfaceLensFlare();

};

