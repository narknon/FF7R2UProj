#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EAIPCTargetLocationType.h"
#include "EndEnvQueryTest_AIPCLineOfSight.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_AIPCLineOfSight : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAIPCTargetLocationType TargetLocationType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool ConsiderWeaponRange;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool ConsiderCheckOnNavmesh;
    
    UEndEnvQueryTest_AIPCLineOfSight();

};

