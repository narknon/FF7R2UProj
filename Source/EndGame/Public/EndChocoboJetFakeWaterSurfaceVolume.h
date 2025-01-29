#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "EndChocoboJetSettingVolumeInterface.h"
#include "EndChocoboJetFakeWaterSurfaceVolume.generated.h"

UCLASS(Blueprintable)
class AEndChocoboJetFakeWaterSurfaceVolume : public AVolume, public IEndChocoboJetSettingVolumeInterface {
    GENERATED_BODY()
public:
    AEndChocoboJetFakeWaterSurfaceVolume(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

