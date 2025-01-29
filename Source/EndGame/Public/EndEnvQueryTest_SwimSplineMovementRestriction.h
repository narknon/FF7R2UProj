#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EndEnvQueryTest_SwimSplineMovementRestriction.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_SwimSplineMovementRestriction : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_bLeaderSwimming;
    
    UEndEnvQueryTest_SwimSplineMovementRestriction();

};

