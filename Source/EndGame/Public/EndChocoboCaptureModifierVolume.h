#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "EEndChocoboCaptureVolumeType.h"
#include "EndChocoboCaptureModifierVolume.generated.h"

UCLASS(Blueprintable)
class AEndChocoboCaptureModifierVolume : public AVolume {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndChocoboCaptureVolumeType _Type;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName _HubID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName _EscapeTargetPoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_WatcherID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_SleepCategoryNumber;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_CheckPointNumber;
    
    AEndChocoboCaptureModifierVolume(const FObjectInitializer& ObjectInitializer);

};

