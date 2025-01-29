#pragma once
#include "CoreMinimal.h"
#include "EEndNavLayerType.h"
#include "EndNavModifierVolumeBase.h"
#include "EndNavModifierAdditionalLayerVolume.generated.h"

UCLASS(Blueprintable)
class AEndNavModifierAdditionalLayerVolume : public AEndNavModifierVolumeBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndNavLayerType LayerType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCreateNav;
    
public:
    AEndNavModifierAdditionalLayerVolume(const FObjectInitializer& ObjectInitializer);

};

