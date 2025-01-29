#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EndEnvQueryTest_InSteeringObstacle.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_InSteeringObstacle : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SteeringParamName;
    
    UEndEnvQueryTest_InSteeringObstacle();

};

