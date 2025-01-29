#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "EndChocoboJetSettingVolumeInterface.h"
#include "EndChocoboJetSettingVolume.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndChocoboJetSettingVolume : public AVolume, public IEndChocoboJetSettingVolumeInterface {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bDisableMoveOnlyNavMesh: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bFakeWaterSurface: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bHeightRestrict: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bApplyEvenIfCharacterOver: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bEnableAutoMoveOverNavMeshTimeOut: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OverrideAutoMoveOverNavMeshCheckDistance;
    
public:
    AEndChocoboJetSettingVolume(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

