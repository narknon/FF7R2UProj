#pragma once
#include "CoreMinimal.h"
#include "EndTriggerBox.h"
#include "EndShootingCoasterSpeedTriggerBox.generated.h"

class AActor;

UCLASS(Blueprintable)
class ENDGAME_API AEndShootingCoasterSpeedTriggerBox : public AEndTriggerBox {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AActor* RailActorReference;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaxLength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AtLength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BoxTag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RideSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LinearInterpolationTime;
    
public:
    AEndShootingCoasterSpeedTriggerBox(const FObjectInitializer& ObjectInitializer);

};

