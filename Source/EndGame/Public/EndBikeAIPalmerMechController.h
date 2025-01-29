#pragma once
#include "CoreMinimal.h"
#include "BikeBreakablePartInfo.h"
#include "BikeLongShotInfo.h"
#include "EndBikeAIControllerEnemyBase.h"
#include "EndBikeAIPalmerMechController.generated.h"

class UPhysicsAsset;

UCLASS(Blueprintable)
class AEndBikeAIPalmerMechController : public AEndBikeAIControllerEnemyBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UPhysicsAsset* ChangePhysicsAsset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FBikeBreakablePartInfo> Parts;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FBikeLongShotInfo> LongShotInfoList;
    
public:
    AEndBikeAIPalmerMechController(const FObjectInitializer& ObjectInitializer);

};

