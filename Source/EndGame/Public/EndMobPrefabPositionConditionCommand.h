#pragma once
#include "CoreMinimal.h"
#include "EndMobPrefabConditionCommand.h"
#include "EndMobPrefabPositionConditionCommand.generated.h"

UCLASS(Blueprintable)
class UEndMobPrefabPositionConditionCommand : public UEndMobPrefabConditionCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DistanceThreshold;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AngleThreshold;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float HeightThreshold;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ContinuationTime;
    
    UEndMobPrefabPositionConditionCommand();

};

