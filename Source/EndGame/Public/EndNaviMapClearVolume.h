#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "EndNaviMapClearVolume.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndNaviMapClearVolume : public AVolume {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LocationId;
    
    AEndNaviMapClearVolume(const FObjectInitializer& ObjectInitializer);

};

