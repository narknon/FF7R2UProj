#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "EndPartyChocoboDisableGetOffOnSwampVolume.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndPartyChocoboDisableGetOffOnSwampVolume : public AVolume {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bDisableGetOff: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bDisableAutoCheck: 1;
    
public:
    AEndPartyChocoboDisableGetOffOnSwampVolume(const FObjectInitializer& ObjectInitializer);

};

