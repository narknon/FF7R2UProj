#pragma once
#include "CoreMinimal.h"
#include "InterpTrackBonamikCharaWindKey.generated.h"

USTRUCT(BlueprintType)
struct FInterpTrackBonamikCharaWindKey {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_Time;
    
    BONAMIKRT_API FInterpTrackBonamikCharaWindKey();
};

