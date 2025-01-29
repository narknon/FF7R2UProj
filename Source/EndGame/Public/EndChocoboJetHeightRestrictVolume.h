#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "EndChocoboJetSettingVolumeInterface.h"
#include "EndChocoboJetHeightRestrictVolume.generated.h"

UCLASS(Blueprintable)
class AEndChocoboJetHeightRestrictVolume : public AVolume, public IEndChocoboJetSettingVolumeInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bApplyEvenIfCharacterOver;
    
    AEndChocoboJetHeightRestrictVolume(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

