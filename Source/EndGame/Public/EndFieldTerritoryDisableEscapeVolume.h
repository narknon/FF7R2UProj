#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "EndFieldTerritoryDisableEscapeVolume.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndFieldTerritoryDisableEscapeVolume : public AVolume {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnablePhysicsBodyBlock;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool IsCubeBoxWallVolume;
    
    AEndFieldTerritoryDisableEscapeVolume(const FObjectInitializer& ObjectInitializer);

};

