#pragma once
#include "CoreMinimal.h"
#include "EndNavBlockingModifierVolume.h"
#include "EndNavSimpleWallVolume.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndNavSimpleWallVolume : public AEndNavBlockingModifierVolume {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float CylinderInnerRadius;
    
public:
    AEndNavSimpleWallVolume(const FObjectInitializer& ObjectInitializer);

};

