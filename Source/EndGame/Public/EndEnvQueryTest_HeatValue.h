#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EEndHeatMapType.h"
#include "EndEnvQueryTest_HeatValue.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_HeatValue : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndHeatMapType HeatType;
    
    UEndEnvQueryTest_HeatValue();

};

