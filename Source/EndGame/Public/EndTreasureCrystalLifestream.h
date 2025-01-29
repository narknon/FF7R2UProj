#pragma once
#include "CoreMinimal.h"
#include "EndTreasureCrystal.h"
#include "EndTreasureCrystalLifestream.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndTreasureCrystalLifestream : public AEndTreasureCrystal {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_EmitStoryFlag;
    
    AEndTreasureCrystalLifestream(const FObjectInitializer& ObjectInitializer);

};

