#pragma once
#include "CoreMinimal.h"
#include "InterpTrackBonamikWorldWindKey.generated.h"

USTRUCT(BlueprintType)
struct FInterpTrackBonamikWorldWindKey {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_Time;
    
    BONAMIKRT_API FInterpTrackBonamikWorldWindKey();
};

