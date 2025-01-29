#pragma once
#include "CoreMinimal.h"
#include "Matinee/InterpTrackFloatBase.h"
#include "InterpTrackBonamikWindControlKey.h"
#include "InterpTrackBonamikWindControl.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class BONAMIKRT_API UInterpTrackBonamikWindControl : public UInterpTrackFloatBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, EditFixedSize, meta=(AllowPrivateAccess=true))
    TArray<FInterpTrackBonamikWindControlKey> m_Keys;
    
    UInterpTrackBonamikWindControl();

};

