#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EndEnvQueryTest_TargetCapsule.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_TargetCapsule : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bConsiderOverrideRadius;
    
    UEndEnvQueryTest_TargetCapsule();

};

