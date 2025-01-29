#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EEndCameraCustomSuspensionType.h"
#include "EndFieldMovementSettingVolumeComponent.generated.h"

class UEndPhysicalMaterial;

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldMovementSettingVolumeComponent : public UBoxComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 MovementSettingFlag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float WaterMoveDepth;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SwimmingWalkableAngle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName HitToLookDownVolumeName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndCameraCustomSuspensionType CameraCustomSuspensionType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndPhysicalMaterial* OverridePhysicalMaterial;
    
    UEndFieldMovementSettingVolumeComponent(const FObjectInitializer& ObjectInitializer);

};

