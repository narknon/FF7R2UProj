#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EndEnvQueryTest_AIPCCommandTargetCapsule.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_AIPCCommandTargetCapsule : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bConsiderOverrideRadius;
    
    UEndEnvQueryTest_AIPCCommandTargetCapsule();

};

