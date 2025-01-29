#pragma once
#include "CoreMinimal.h"
#include "InterpTrackBonamikTeleportKey.generated.h"

USTRUCT(BlueprintType)
struct FInterpTrackBonamikTeleportKey {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_Time;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_Distance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_PreRoll;
    
    BONAMIKRT_API FInterpTrackBonamikTeleportKey();
};

