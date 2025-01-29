#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "WallRunningBlockBoxVolume.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UWallRunningBlockBoxVolume : public UBoxComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bForceHitToJump;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisableWallCorrect;
    
    UWallRunningBlockBoxVolume(const FObjectInitializer& ObjectInitializer);

};

