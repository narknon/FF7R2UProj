#pragma once
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "EndWarpPoint.generated.h"

UCLASS(Blueprintable)
class AEndWarpPoint : public ATargetPoint {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName UniqueId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool UnlistDebugWarp;
    
    AEndWarpPoint(const FObjectInitializer& ObjectInitializer);

};

