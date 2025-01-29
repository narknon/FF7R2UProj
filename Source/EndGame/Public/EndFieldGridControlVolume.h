#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "EEndFieldGridControlType.h"
#include "EndFieldGridControlVolume.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndFieldGridControlVolume : public AVolume {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndFieldGridControlType ControlType;
    
    AEndFieldGridControlVolume(const FObjectInitializer& ObjectInitializer);

};

