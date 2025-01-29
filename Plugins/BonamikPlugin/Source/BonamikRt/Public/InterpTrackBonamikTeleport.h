#pragma once
#include "CoreMinimal.h"
#include "Matinee/InterpTrack.h"
#include "InterpTrackBonamikTeleportKey.h"
#include "InterpTrackBonamikTeleport.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class BONAMIKRT_API UInterpTrackBonamikTeleport : public UInterpTrack {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, EditFixedSize, meta=(AllowPrivateAccess=true))
    TArray<FInterpTrackBonamikTeleportKey> m_Keys;
    
    UInterpTrackBonamikTeleport();

};

