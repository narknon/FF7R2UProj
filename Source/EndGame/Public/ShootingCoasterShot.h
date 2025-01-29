#pragma once
#include "CoreMinimal.h"
#include "ShootingCoasterShot.generated.h"

class AActor;

USTRUCT(BlueprintType)
struct FShootingCoasterShot {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<TWeakObjectPtr<AActor>> ActorsToIgnore;
    
    ENDGAME_API FShootingCoasterShot();
};

