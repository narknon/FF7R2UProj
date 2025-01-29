#pragma once
#include "CoreMinimal.h"
#include "EndNavSimpleWallVolume.h"
#include "EndNavWheelieBlockWallVolume.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndNavWheelieBlockWallVolume : public AEndNavSimpleWallVolume {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TriggerName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TriggerInterval;
    
public:
    AEndNavWheelieBlockWallVolume(const FObjectInitializer& ObjectInitializer);

};

