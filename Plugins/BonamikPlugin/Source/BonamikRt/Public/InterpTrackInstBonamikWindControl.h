#pragma once
#include "CoreMinimal.h"
#include "Matinee/InterpTrackInst.h"
#include "InterpTrackInstBonamikWindControl.generated.h"

UCLASS(Blueprintable)
class BONAMIKRT_API UInterpTrackInstBonamikWindControl : public UInterpTrackInst {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_LastKeyIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_BackupWindScale;
    
    UInterpTrackInstBonamikWindControl();

};

