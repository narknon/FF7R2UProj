#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EEndNavLayerType.h"
#include "EEndQueryFilterType.h"
#include "EndEnvQueryTest_DistanceToWall.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_DistanceToWall : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndNavLayerType NavLayerType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndQueryFilterType QueryFilterType;
    
    UEndEnvQueryTest_DistanceToWall();

};

