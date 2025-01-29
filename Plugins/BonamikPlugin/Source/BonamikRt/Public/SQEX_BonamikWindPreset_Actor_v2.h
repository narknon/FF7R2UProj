#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SQEX_BonamikWindPreset_Actor_v2.generated.h"

class USQEX_BonamikWindCollectionAsset_v2;

UCLASS(Blueprintable, Deprecated, NotPlaceable)
class BONAMIKRT_API ADEPRECATED_SQEX_BonamikWindPreset_Actor_v2 : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEX_BonamikWindCollectionAsset_v2* m_BonamikWindCollectionAsset;
    
    ADEPRECATED_SQEX_BonamikWindPreset_Actor_v2(const FObjectInitializer& ObjectInitializer);

};

