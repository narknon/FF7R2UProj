#pragma once
#include "CoreMinimal.h"
#include "Matinee/InterpTrackInst.h"
#include "InterpTrackInstBonamikWorldWind.generated.h"

class USQEX_Bonamik_Component;

UCLASS(Blueprintable)
class BONAMIKRT_API UInterpTrackInstBonamikWorldWind : public UInterpTrackInst {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USQEX_Bonamik_Component* m_Comp;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_LastKeyIndex;
    
    UInterpTrackInstBonamikWorldWind();

};

