#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "EndChocoboJetSettingVolumeInterface.h"
#include "EndChocoboJetMovementSettingVolume.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndChocoboJetMovementSettingVolume : public AVolume, public IEndChocoboJetSettingVolumeInterface {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bDisableMoveOnlyNavMesh: 1;
    
public:
    AEndChocoboJetMovementSettingVolume(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

