#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndWeaponSwimCameraLookAtConfig.h"
#include "WeaponSwimCameraConfigComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UWeaponSwimCameraConfigComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float CameraRotationInterpSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndWeaponSwimCameraLookAtConfig> LookAtConfigs;
    
    UWeaponSwimCameraConfigComponent(const FObjectInitializer& ObjectInitializer);

};

