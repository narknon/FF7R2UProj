#pragma once
#include "CoreMinimal.h"
#include "InterpTrackBonamikWindControlKey.generated.h"

USTRUCT(BlueprintType)
struct FInterpTrackBonamikWindControlKey {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_Time;
    
    BONAMIKRT_API FInterpTrackBonamikWindControlKey();
};

